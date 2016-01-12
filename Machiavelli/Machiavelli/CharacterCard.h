#pragma once
#include "Card.h"
#include <string>

using namespace std;

class CharacterCard :
	public Card
{
public:
	CharacterCard(int _id, string _name, ColorEnum _color) : Card(_name, _color) { id = _id; };
	~CharacterCard();
private:
	int id;
};

