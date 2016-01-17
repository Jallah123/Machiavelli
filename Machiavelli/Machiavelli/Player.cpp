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
	for (auto& card: cards)
	{
		auto& it = find(handCards.begin(), handCards.end(), card);
		if (it != handCards.end())
		{
			handCards.erase(it);
		}
	}
}
