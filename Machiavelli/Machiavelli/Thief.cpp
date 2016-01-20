#include "Thief.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>
#include "SocketUtil.h"

void Thief::Action()
{
	auto& socket = owner.get()->GetSocket();
	int number = -1;
	while (true) {
		socket.write("Choose number you want to rob.\r\n");
		auto t = game->getCharacters();
		for each (auto& character in t)
		{
			socket.write(character->GetId() + ". " + stoi(character->GetName()));
		}
		int number = SocketUtil::GetNumber(owner, 8, 3);

		if (number == -1)
		{
			return;
		}
		else 
		{
			break;
		}
	}
	game->getCharacters().at(number)->Rob();
	ActionDone = true;
}