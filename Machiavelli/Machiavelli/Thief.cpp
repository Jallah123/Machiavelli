#include "Thief.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>
#include "SocketUtil.h"

void Thief::Action()
{
	auto& socket = owner.get()->GetSocket();

	socket.write("Choose number you want to rob.\r\n");
	auto t = game->getCharacters();
	for each (auto& character in t)
	{
		if (character->GetId() > 2) 
		{
			socket.write(to_string(character->GetId()) + ". " + character->GetName() + "\r\n");
		}
	}
	int number = SocketUtil::GetNumber(owner, 8, 3);

	if (number == -1)
	{
		return;
	}

	game->getCharacters().at(number - 1)->Rob();
	ActionDone = true;
}