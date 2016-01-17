#include "Thief.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>

void Thief::Action()
{
	auto& socket = owner.get()->GetSocket();
	int number = -1;
	while (number == -1 && number < game->getCharacters().size() && number > 2) {
		socket.write("Choose number you want to rob.");
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
	game->getCharacters().at(number)->Rob();
	ActionDone = true;
}