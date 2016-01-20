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

	for (auto& character : game->getCharacters())
	{
		if (character->GetId() != 1)
		{
			socket.write(to_string(character->GetId()) + ". " + character->GetName() + "\r\n");
		}
	}

	int number = SocketUtil::GetNumber(owner, game->getCharacters().size(), 2);

	if (number == -1)
	{
		return;
	}

	game->getCharacters().at(number - 1)->Kill();
	ActionDone = true;
	owner->ResetLastCommand();
}