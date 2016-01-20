//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"
#include <algorithm>
#include "GameController.h"
#include "CharacterCard.h"
#include "SocketUtil.h"

using namespace std;

void Player::DeleteFromHand(vector<shared_ptr<BuildingCard>> cards)
{
	for (auto& card : cards)
	{
		auto& it = find(handCards.begin(), handCards.end(), card);
		if (it != handCards.end())
		{
			handCards.erase(it);
		}
	}
}

void Player::BuildBuilding(shared_ptr<BuildingCard> building)
{
	RemoveGold(building->GetCost());
	playedCards.push_back(building);
	handCards.erase(find(handCards.begin(), handCards.end(), building));
}

void Player::DiscardCharacter()
{
	vector<shared_ptr<CharacterCard>> characters = game->getCharacters();
	socket->write("Please discard a character:\r\n");
	for (auto& character : characters)
	{
		if (!character->IsDiscarded() && character->GetOwner() == nullptr)
		{
			socket->write(to_string(character->GetId()) + ". " + character->GetName() + "\r\n");
		}
	}
	bool running = true;
	while (running)
	{
		int choice = SocketUtil::GetNumber(game->GetSharedPlayer(*this), characters.size());
		for (auto& character : characters)
		{
			if (character->GetId() == choice)
			{
				if (!character->IsDiscarded() && character->GetOwner() == nullptr)
				{
					character->Discard();
					running = false;
					break;
				}
				else
				{
					socket->write("Character already chosen or discarded.\r\n");
				}
			}
		}
	}
	ResetLastCommand();
}

void Player::ShowInfo()
{
	socket->write("Goud : " + to_string(gold) + "\r\n");

	socket->write("Gebouwen : \r\n");
	for (auto& building : playedCards)
	{
		socket->write(building->GetInfo());
	}
	socket->write("\r\nHandkaarten : \r\n");
	for (auto& building : handCards)
	{
		socket->write(building->GetInfo());
	}
	socket->write("\r\n");
}

string Player::GetInfo()
{
	string s = "";
	s += "Goud : " + to_string(gold) + "\r\n";

	s += "Gebouwen : \r\n";
	for (auto& building : playedCards)
	{
		s += building->GetInfo();
	}
	s += "\r\n";
	return s;
}



void Player::ChooseCharacter()
{
	vector<shared_ptr<CharacterCard>> characters = game->getCharacters();
	socket->write("Please pick a character:\r\n");
	for (auto& character : characters)
	{
		if (!character->IsDiscarded() && character->GetOwner() == nullptr)
		{
			socket->write(to_string(character->GetId()) + ". " + character->GetName() + "\r\n");
		}
	}
	bool running = true;
	while (running)
	{
		int choice = SocketUtil::GetNumber(game->GetSharedPlayer(*this), characters.size());
		for (auto& character : characters)
		{
			if (character->GetId() == choice)
			{
				if (!character->IsDiscarded() && character->GetOwner() == nullptr)
				{
					characterCards.push_back(character);
					character->SetOwner(game->GetSharedPlayer(*this));
					running = false;
					break;
				}
				else
				{
					socket->write("Character already chosen or discarded.\r\n");
				}
			}
		}
	}
	ResetLastCommand();
	socket->write("Waiting for other player ");
}
