#include "Mage.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include "Utility.h"
#include <string>

Mage::Mage(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
}


void Mage::Action()
{
	auto& socket = owner.get()->GetSocket();
	int number = -1;
	if (owner->GetHand().size() == 0)
	{
		socket.write("You have no cards in your hand, automatically swapping with other player.");
		SwapCards();
	}
	// While number is not in range of 1-2
	while (!(number >= 1 && number <= 2))
	{
		socket.write("Choose:\n1. Trade hand with other player.\n2. Discard cards and get new ones.");
		string line = socket.readline();
		if (line == "cancel")
		{
			return;
		}
		number = stoi(line);
	}
	if (number == 1)
	{
		SwapCards();
	}
	else if (number == 2)
	{
		DiscardCards();
	}
	ActionDone = true;
}

void Mage::SwapCards()
{
	auto& other = game->GetOtherPlayer(owner);
	swap(other->GetHand(), owner->GetHand());
}

void Mage::DiscardCards()
{
	auto& socket = owner->GetSocket();
	int number = -1;
	int amountCardsInHand = owner->GetHand().size();
	// While number is not in range of 1-2

	socket.write("You hand:\n");
	int i = 0;
	for each (auto& card in owner->GetHand())
	{
		socket.write(to_string(i++) + card->GetName() + " " + card->GetColor() + '\n');
	}

	socket.write("\nPlease enter the cards you want to discard. (2,3,6)\n");
	string line = socket.readline();
	if (line == "cancel")
	{
		return;
	}
	vector<string> cardsSplit;
	Utility::split(line, ',', cardsSplit);
	vector<shared_ptr<BuildingCard>> cards;
	for each (auto s in cardsSplit)
	{
		cards.push_back(owner->GetHand().at(stoi(s)));
	}
	owner->DeleteFromHand(cards);
	game->SwapCards(owner, cards);
}

Mage::~Mage()
{
}
