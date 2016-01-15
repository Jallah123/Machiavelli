#include "Warlord.h"
#include "Player.hpp"
#include "GameController.h"

Warlord::Warlord(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
}


void Warlord::Action()
{
	GetGoldForBuildings();
	auto& socket = owner->GetSocket();
	auto& p = game->GetOtherPlayer(owner);
	socket.write("Building:\n");

	for (int i = 0; i < p->GetPlayedCards().size(); i++)
	{
		socket.write(to_string(i) + ". " + p->GetPlayedCards().at(i)->GetName() + " price: " + to_string(p->GetPlayedCards().at(i)->GetCost() - 1) + '\n');
	}

	int number = -1;
	while (number == -1)
	{
		socket.write("Which building do you want to destroy?(cancel to return):\n");
		string line = socket.readline();
		if (line == "cancel")
		{
			return;
		}
		int number = stoi(line);
		if (number < p->GetPlayedCards().size() && number >= 0)
		{

		}
	}
	ActionDone = true;
}

Warlord::~Warlord()
{
}
