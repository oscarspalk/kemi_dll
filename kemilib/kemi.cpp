#include "pch.h"
#include "kemi.h"
#include <string>
#include "Element.h"
#include <vector>
#include "json.h"
#include <iostream>
#include <fstream>

std::vector<Element> elements;

struct ElementWithAmount {
	Element element;
	int amount;
};

std::vector<std::string> split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(s.substr(pos_start));
	return res;
}

std::vector<std::string> seperateElements(std::string input) {
	std::vector<std::string> elementsSplitted = std::vector<std::string>();
	size_t strLength = input.length();
	bool containsDouble = false;
	int backtrack = 0;
	for (size_t i = 0; i < strLength; i++)
	{
		char c = input.at(i);
		if ((i+1 < strLength) && input.at(i+1) == '_') {
			std::string rest = input.substr(i - backtrack, strLength);
			elementsSplitted.push_back(rest);
			return elementsSplitted;
		}
		if ((i+1 < strLength) && isupper(input.at(i + 1)) || i+1 == strLength) {
			std::string whatToAdd = "";
			for (size_t j = 0; j < backtrack+1; j++) {
				whatToAdd =  input.at(i-j) + whatToAdd;
			}
			elementsSplitted.push_back(whatToAdd);
			containsDouble = true;
			backtrack = 0;

		}
		else {
			backtrack++;
		}

	}
	if (!containsDouble) {
		elementsSplitted.push_back(input);
		return elementsSplitted;
	}
	return elementsSplitted;
}

ElementWithAmount extractElement(std::string str) {
	std::vector<std::string> keyValue = split(str, "__");
	int amount = 0;
	std::string symbol = "";
	if (keyValue.size() == 1) {
		symbol = str;
		amount = 1;
	}
	else {
		symbol = keyValue[0];
		auto potensSplitted = split(keyValue[1], "^");
		if (potensSplitted.size() == 1) {
			amount = atoi(potensSplitted[0].c_str());
		}
		else {
			int normalAmount = atoi(potensSplitted[0].c_str());
			int multiplier = atoi(potensSplitted[1].c_str());
			amount = normalAmount * multiplier;
		}
	}

	for (auto element : elements) {
		if (element.symbol == symbol) {
			ElementWithAmount elWithAmount = {
				element,
				amount
			};
			return elWithAmount;
		}
	}

}

std::vector<ElementWithAmount> extractMolecule(std::string molecule) {
	std::vector<ElementWithAmount> buildElements = std::vector<ElementWithAmount>();
	std::vector<std::string> differentElements = split(molecule, "*");
	for (std::string element : differentElements) {
		std::vector<std::string> subElements = seperateElements(element);
		for (std::string subElement : subElements) {
			buildElements.push_back(extractElement(subElement));
		}
	}
	return buildElements;
}

double M(char* input) {
	double totalMass = 0.0;
	std::vector<ElementWithAmount> builtOfElements = extractMolecule(input);
	for (auto element : builtOfElements) {
		totalMass += element.element.atomic_mass * element.amount;
	}
	return totalMass;
}

void initlib(char* datapath) {
	std::ifstream myfile(std::string(datapath) + "/data/kemi/elements.json");
	nlohmann::json elementsJson = nlohmann::json::parse(myfile);
	nlohmann::json arrElements = elementsJson["elements"];
	for (nlohmann::json::iterator it = arrElements.begin(); it != arrElements.end(); ++it) {
		nlohmann::json element = *it;
		elements.push_back( Element(element["name"], element["symbol"], element["atomic_mass"]));
	}
}

const char* G(int num) {
	return elements[num].name.c_str();
}