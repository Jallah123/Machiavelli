#include "Utility.h"
#include <iostream>
#include <random>
#include <sstream>

Utility::Utility()
{
}


Utility::~Utility()
{
}

Utility* Utility::instance{ nullptr }; // definition & init

Utility* Utility::GetInstance() {
	if (instance == nullptr) {
		instance = new Utility;
	}
	return instance;
}

int Utility::RandomNumber(int min, int max)
{
	random_device dev;
	default_random_engine dre{ dev() };
	uniform_int_distribution<int> dist{ min, max };

	return dist(dre);
}

vector<string>& Utility::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}