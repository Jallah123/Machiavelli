#pragma once
#include "Card.h"
#include <string>

class BuildingCard :
	public Card
{
public:
	BuildingCard(string _name, ColorEnum _color, int _cost) : Card(_name, _color) { cost = _cost; };
	string GetInfo() { return GetName() + " (" + GetColor() + ", " + to_string(GetCost()) + ")\r\n"; };
	int GetCost() { return cost; };
private:
	int cost;
};