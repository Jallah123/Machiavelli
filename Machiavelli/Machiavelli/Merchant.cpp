#include "Merchant.h"
#include "Player.hpp"

void Merchant::BeginTurn()
{
	owner->AddGold(1);
}


void Merchant::Action()
{
	GetGoldForBuildings();
	ActionDone = true;
}