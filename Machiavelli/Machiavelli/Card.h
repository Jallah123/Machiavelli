#pragma once
#include <string>
#include "ColorEnum.h"

using namespace std;

class Card
{
public:
	Card() {};
	Card(string _name, ColorEnum _color) : name(_name), color(_color) {};
	string GetName() { return name; };
	string GetColor() {
		for each (auto& c in ColorMap)
		{
			if (c.second == color)
				return c.first;
		}
		return "No such color.";
	};
protected:
	string name;
	ColorEnum color;
};