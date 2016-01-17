#include "Murderer.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>
#include "CharacterCard.h"

void Murderer::Action()
{
	// conversatie/kiezen
	auto& socket = owner.get()->GetSocket();
	int number = -1;
	while (number == -1 && number < game->getCharacters().size() && number > 1) {
		socket.write("Choose number you want to kill.");
		auto t = game->getCharacters();
		for each (auto& character in t)
		{
			socket.write(character->GetId() + ". " + stoi(character->GetName()));
		}
		string line = owner.get()->GetSocket().readline();
		if (line == "cancel")
		{
			return;
		}
		number = stoi(line);
	}
	game->getCharacters().at(number)->Kill();
	ActionDone = true;
}