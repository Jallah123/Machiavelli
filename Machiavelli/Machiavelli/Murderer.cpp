#include "Murderer.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>
#include "CharacterCard.h"
#include "SocketUtil.h"

void Murderer::Action()
{
	// conversatie/kiezen
	auto& socket = owner.get()->GetSocket();

	socket.write("Choose number you want to kill.");

	for each (auto& character in game->getCharacters())
	{
		socket.write(character->GetId() + ". " + stoi(character->GetName()));
	}

	int number = SocketUtil::GetNumber(owner, 8);

	if (number == -1)
	{
		return;
	}
	
	game->getCharacters().at(number)->Kill();
	ActionDone = true;
}