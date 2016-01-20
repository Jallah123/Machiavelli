#include "Warlord.h"
#include "Player.hpp"
#include "GameController.h"
#include "SocketUtil.h"

void Warlord::Action()
{
	auto& socket = owner->GetSocket();
	auto& p = game->GetOtherPlayer(owner);
	for (auto& character : p->GetCharacterCards())
	{
		// Other player has preacher
		if (character->GetId() == 5)
		{
			socket.write("Other player has preacher, can't destroy his buildings.\r\n");
			ActionDone = true;
			return;
		}
	}
	socket.write("Building:\r\n");

	for (size_t i = 0; i < p->GetPlayedCards().size(); i++)
	{
		socket.write(to_string(i) + ". " + p->GetPlayedCards().at(i)->GetName() + " price: " + to_string(p->GetPlayedCards().at(i)->GetCost() - 1) + "\r\n");
	}

	int number = -1;

	socket.write("Which building do you want to destroy?(cancel to return):\r\n");
	number = SocketUtil::GetNumber(owner, p->GetPlayedCards().size() - 1);

	if (number == -1)
	{
		return;
	}

	if (owner->GetGold() >= p->GetPlayedCards().at(number)->GetCost() - 1)
	{
		owner->RemoveGold(p->GetPlayedCards().at(number)->GetCost() - 1);
		p->DestroyBuilding(p->GetPlayedCards().at(number));
	}
	else
	{
		socket.write("Too expensive.\r\n");
		return;
	}

	ActionDone = true;
}