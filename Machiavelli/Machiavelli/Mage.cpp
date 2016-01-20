#include "Mage.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include "Utility.h"
#include <string>
#include "SocketUtil.h"

void Mage::Action()
{
	auto& socket = owner.get()->GetSocket();
	int number = -1;
	if (owner->GetHand().size() == 0)
	{
		socket.write("You have no cards in your hand, automatically swapping with other player.");
		SwapCards();
	}
	number = SocketUtil::GetNumber(owner, 2, 1);

	if (number == -1)
	{
		return;
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