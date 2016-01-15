#pragma once
#include <string>
#include "ColorEnum.h"

using namespace std;

class Card
{
public:
	Card(string _name, ColorEnum _color) : name(_name), color(_color) {};
	string GetName() { return name; }
protected:
	string name;
	ColorEnum color;
};