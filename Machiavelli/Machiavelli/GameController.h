#pragma once
#include "CardFactory.h"
#include "GameState.h"
#include "Player.hpp"
#include "Card.h"

class GameController
{
public:
	GameController();
	~GameController() {};
	void setState(GameState newState) { currentState = newState; };
	void addPlayer(shared_ptr<Player> player);
	GameState& getState() { return currentState; };
	shared_ptr<CharacterCard> chooseCharacterCard(int card);
	shared_ptr<BuildingCard> TakeCard();
	vector<shared_ptr<CharacterCard>> getCharacters() { return characterCards; };
	shared_ptr<Player> GetOtherPlayer(shared_ptr<Player> self);
	void GiveStartingResources();
	void ChooseCharacters();
	void HandleCommand(shared_ptr<Player> player, string cmd);
	void SwapCards(shared_ptr<Player> p, vector<shared_ptr<BuildingCard>> cards);
	void SetNewKing(shared_ptr<Player> _NewKing) { NewKing = _NewKing; };
	void SetKing() { King = GetOldestPlayer(); CurrentPlayer = King; };
	shared_ptr<Player> GetKing() { return King; };
private:
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildingCard>> buildingCards;
	void createCharacterCards();
	void createBuildingCards();
	void StartGame();
	GameState currentState;
	vector<shared_ptr<Player>> players;
	shared_ptr<Player> King = nullptr;
	shared_ptr<Player> NewKing = nullptr;
	shared_ptr<Player> CurrentPlayer = nullptr;
	shared_ptr<Player> GetOldestPlayer();
	shared_ptr<BuildingCard> RandomCard(vector<shared_ptr<BuildingCard>> cards);
	shared_ptr<CharacterCard> RandomCard(vector<shared_ptr<CharacterCard>> cards);
};