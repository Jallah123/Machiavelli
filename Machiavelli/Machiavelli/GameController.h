#pragma once
#include "CardFactory.h"
#include "GameState.h"
#include "Player.hpp"

class GameController
{
public:
	GameController();
	~GameController();
	void setState(GameState newState) { currentState = newState; };
	void addPlayer(shared_ptr<Player> player) 
	{ 
		players.push_back(player); 
		if (players.size() == 2)
		{
			currentState = SETUP;
		}
	}
	GameState& getState() { return currentState; };
	shared_ptr<CharacterCard> chooseCharacterCard(int card);
	shared_ptr<BuildingCard> takeCard();
	vector<shared_ptr<CharacterCard>> getCharacters() { return characterCards; };
private:
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildingCard>> buildingCards;
	void createCharacterCards();
	void createBuildingCards();
	GameState currentState;
	vector<shared_ptr<Player>> players;
	shared_ptr<Player> King;
	shared_ptr<Player> NewKing;
	shared_ptr<Player> getOldestPlayer();
};