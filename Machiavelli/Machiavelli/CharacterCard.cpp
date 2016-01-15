#include "CharacterCard.h"
#include "Player.hpp"

void CharacterCard::GetGoldForBuildings()
{
	for each (auto& card in owner->GetPlayedCards())
	{
		if (card->GetColor() == GetColor())
		{
			owner->GetSocket().write("You receive 1 gold for .\n");
			owner->AddGold(1);
		}
	}
	GoldReceived = true;
}
