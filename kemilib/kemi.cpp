#include "pch.h"
#include "kemi.h"
#include <string>
#include "Element.h"
#include <vector>
#include "json.h"
#include <iostream>
#include <fstream>

std::vector<Element> elements;

char* M(char* input) {
	return input;
}

void initlib() {
	std::ifstream myfile("C:/Users/knudi/source/repos/kemi_dll/kemilib/elements.json");
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