#include "CardFactory.h"
#include "Parser.h"
#include <string>

unique_ptr<CharacterCard> CardFactory::createCharacterCard(int _id, string _name, ColorEnum _color)
{
	return unique_ptr<CharacterCard>(new CharacterCard(_id, _name, _color));
}

shared_ptr<BuildingCard> CardFactory::createBuildingCard(string _name, ColorEnum _color, int _cost)
{
	return shared_ptr<BuildingCard>(new BuildingCard(_name, _color, _cost));
}