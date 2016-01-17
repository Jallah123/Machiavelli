#include "CardFactory.h"
#include "BuildingCard.h"
#include "CharacterCard.h"
#include "Murderer.h"
#include "Thief.h"
#include "Mage.h"
#include "King.h"
#include "Preacher.h"
#include "Merchant.h"
#include "Architect.h"
#include "Warlord.h"

std::map<std::string, std::shared_ptr<CharacterCard>> CardFactory::FillMap()
{
	std::map<std::string, shared_ptr<CharacterCard>> map;

	map["Moordenaar"] = shared_ptr<Murderer>(new Murderer);
	map["Dief"] = shared_ptr<Thief>(new Thief);
	map["Magiër"] = shared_ptr<Mage>(new Mage);
	map["Koning"] = shared_ptr<King>(new King);
	map["Prediker"] = shared_ptr<Preacher>(new Preacher);
	map["Koopman"] = shared_ptr<Merchant>(new Merchant);
	map["Bouwmeester"] = shared_ptr<Architect>(new Architect);
	map["Condottiere"] = shared_ptr<Warlord>(new Warlord);

	return map;
}

shared_ptr<CharacterCard> CardFactory::createCharacterCard(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game)
{
	shared_ptr<CharacterCard> instance;
	auto it = CardFactory::Instance()->cards.find(_name);
	if (it != CardFactory::Instance()->cards.end())
		instance = it->second;

	instance->Initialize(_id, _name, _color, _game);
	return instance;
}

shared_ptr<BuildingCard> CardFactory::createBuildingCard(string _name, ColorEnum _color, int _cost)
{
	return shared_ptr<BuildingCard>(new BuildingCard(_name, _color, _cost));
}