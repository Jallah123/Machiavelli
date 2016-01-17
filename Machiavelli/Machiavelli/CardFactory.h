#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Card.h"

using namespace std;

class BuildingCard;
class CharacterCard;
class GameController;

class CardFactory
{
public:
	static CardFactory* Instance() {//Singleton
		static CardFactory f;
		return &f;
	}
	shared_ptr<BuildingCard> createBuildingCard(string _name, ColorEnum _color, int _cost);
	shared_ptr<CharacterCard> createCharacterCard(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	map<string, shared_ptr<CharacterCard>> FillMap();
private:
	CardFactory() { cards = FillMap(); };
	map<string, shared_ptr<CharacterCard>> cards;
};