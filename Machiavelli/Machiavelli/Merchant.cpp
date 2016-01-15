#include "Merchant.h"
#include "Player.hpp"

Merchant::Merchant(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
}

void Merchant::BeginTurn()
{
	owner->AddGold(1);
}


void Merchant::Action()
{
	GetGoldForBuildings();
}

Merchant::~Merchant()
{
}
