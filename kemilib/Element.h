#include <string>
#pragma once

class Element
{
public:

	Element(double n, double sym, double m) {
		atomic_mass = m;
		symbol = sym;
		name = n;
	}

	double atomic_mass;
	std::string symbol;
	std::string name;
};
