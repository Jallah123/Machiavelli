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
	Player(const std::string& name, const int& day, const int& month, const int& year, shared_ptr<Socket> _socket, shared_ptr<GameController> _game) : name{ name }, socket(_socket) { age.tm_mday = day; age.tm_mon = month; age.tm_year = year; game = _game; }
	
	// Setters
	void SetGold(int amount) { gold = amount; };
	void setName(const std::string& new_name) { name = new_name; }
	void SetHand(vector<shared_ptr<BuildingCard>> newHand) { handCards = newHand; };
	void SetLastCommand(string command) { lastCommand = command; };

	// Getters
	vector<shared_ptr<CharacterCard>> GetCharacterCards() { return characterCards; };
	vector<shared_ptr<BuildingCard>> GetPlayedCards() { return playedCards; };
	vector<shared_ptr<BuildingCard>> GetHand() { return handCards; };
	Socket& GetSocket() { return *socket.get(); };
	tm getAge() { return age; };
	string getName() const { return name; }
	int GetGold() { return gold; };
	shared_ptr<GameController> GetGameController() { return game; };
	string GetLastCommand() { return lastCommand; };

	// Other
	void DeleteFromHand(vector<shared_ptr<BuildingCard>> cards);
	void AddCardToHand(shared_ptr<BuildingCard> card) { handCards.push_back(card); };
	void AddGold(int amount) { gold += amount; };
	void RemoveGold(int amount) { gold -= amount; };
	void DestroyBuilding(shared_ptr<BuildingCard> building) { playedCards.erase(find(playedCards.begin(), playedCards.end(), building)); };
	void BuildBuilding(shared_ptr<BuildingCard> building);
	void ChooseCharacter();
	void DiscardCharacter();
	void ResetLastCommand() { lastCommand = ""; };
	void ShowInfo();
	string GetInfo();
private:
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildingCard>> playedCards;
	vector<shared_ptr<BuildingCard>> handCards;
	shared_ptr<Socket> socket;
	shared_ptr<GameController> game = nullptr;
	int gold = 2;
	string name;
	tm age;
	string lastCommand = "";
};

#endif /* Player_hpp */
