#pragma once
#include "Card.h"

class BuildingCard :
	public Card
{
public:
	BuildingCard(string _name, ColorEnum _color, int _cost) : Card(_name, _color) { cost = _cost; };
private:
	int cost;
};