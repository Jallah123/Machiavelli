//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"
#include <algorithm>

using namespace std;

void Player::DeleteFromHand(vector<shared_ptr<BuildingCard>> cards)
{
	/*
	handCards.erase(std::remove(cards.begin(), cards.end(), cards.size()), cards.end());
	for each (auto& card in handCards)
	{
		remove(handCards.begin(), handCards.end(), find(cards.begin(), cards.end(), card));
		handCards.erase(find(cards.begin(), cards.end(), card));
	}*/
}
