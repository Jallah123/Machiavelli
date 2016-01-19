#include "Thief.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include <string>

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
		socket.write(machiavelli::prompt);
		string line = owner->GetLastCommand();
		if (line == "cancel")
		{
			return;
		}
		try
		{
			number = stoi(line);
		}
		catch (...)
		{
			socket.write("Je hebt geen nummer gekozen.\r\n");
		}
		if (number > 2 && number < game->getCharacters().size())
		{
			break;
		}
	}
	game->getCharacters().at(number)->Rob();
	ActionDone = true;
}