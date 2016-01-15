//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <vector>
#include <memory>
#include "CharacterCard.h"
#include "BuildingCard.h"
#include "Socket.h"

using namespace std;

class Player {
public:
	Player(const std::string& name, const int& day, const int& month, const int& year, shared_ptr<Socket> _socket) : name{ name }, socket(_socket) { age.tm_mday = day; age.tm_mon = month; age.tm_year = year; }

	std::string getName() const { return name; }
	void setName(const std::string& new_name) { name = new_name; }
	Socket& GetSocket() { return *socket.get(); };
	tm getAge() { return age; };
	vector<shared_ptr<BuildingCard>> GetHand() { return handCards; };
	void SetHand(vector<shared_ptr<BuildingCard>> newHand) { handCards = newHand; };
	void DeleteFromHand(vector<shared_ptr<BuildingCard>> cards);
	vector<shared_ptr<BuildingCard>> GetPlayedCards() { return playedCards; };
	void AddGold(int amount) { gold += amount; };
	void Remove(int amount) { gold -= amount; };
private:
	std::string name;
	tm age;
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildingCard>> playedCards;
	vector<shared_ptr<BuildingCard>> handCards;
	shared_ptr<Socket> socket;
	int gold = 2;
};

#endif /* Player_hpp */
