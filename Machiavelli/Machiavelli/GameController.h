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
private:
	vector<unique_ptr<CharacterCard>> characterCards;
	vector<unique_ptr<BuildingCard>> buildingCards;
	void createCharacterCards();
	void createBuildingCards();
	GameState currentState;
	vector<Player> players;
};