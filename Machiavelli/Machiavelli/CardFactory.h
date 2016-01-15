#pragma once
#include "BuildingCard.h"
#include "CharacterCard.h"
#include <vector>
#include <memory>

class CardFactory
{
public:
	static unique_ptr<BuildingCard> createBuildingCard(string _name, ColorEnum _color, int _cost);
	static unique_ptr<CharacterCard> createCharacterCard(int _id, string _name, ColorEnum _color);
};