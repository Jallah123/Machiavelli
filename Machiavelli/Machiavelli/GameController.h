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
	unique_ptr<CharacterCard> chooseCharacterCard(int card);
	unique_ptr<BuildingCard> takeCard();
private:
	vector<unique_ptr<CharacterCard>> characterCards;
	vector<unique_ptr<BuildingCard>> buildingCards;
	void createCharacterCards();
	void createBuildingCards();
	GameState currentState;
	vector<shared_ptr<Player>> players;
	shared_ptr<Player> getOldestPlayer();
};