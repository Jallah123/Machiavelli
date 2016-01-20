#pragma once
#include "CardFactory.h"
#include "GameState.h"
#include "Player.hpp"
#include "Card.h"
#include "Machiavelli.h"

class GameController
{
public:
	GameController();
	~GameController() {};
	void setState(GameState newState) { currentState = newState; };
	void addPlayer(shared_ptr<Player> player);
	GameState& getState() { return currentState; };
	shared_ptr<CharacterCard> chooseCharacterCard(size_t card);
	shared_ptr<BuildingCard> TakeCard();
	vector<shared_ptr<CharacterCard>>& getCharacters() { return characterCards; };
	shared_ptr<Player> GetOtherPlayer(shared_ptr<Player> self);
	void GiveStartingResources();
	void ChooseCharacters();
	void HandleCommand(shared_ptr<Player> player, string cmd);
	void SwapCards(shared_ptr<Player> p, vector<shared_ptr<BuildingCard>> cards);
	void SetNewKing(shared_ptr<Player> _NewKing) { NewKing = _NewKing; };
	void SetKing() { King = NewKing; CurrentPlayer = King; };
	shared_ptr<Player> GetKing() { return King; };
	void StartGame();
	shared_ptr<Player> GetSharedPlayer(Player& p);
	void Finish(shared_ptr<Player> player);
private:
	void ShowScore();
	void WriteToAll(string s);
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildingCard>> buildingCards;
	void createCharacterCards();
	void createBuildingCards();
	GameState currentState;
	vector<shared_ptr<Player>> players;
	shared_ptr<Player> King = nullptr;
	shared_ptr<Player> NewKing = nullptr;
	shared_ptr<Player> CurrentPlayer = nullptr;
	shared_ptr<Player> GetOldestPlayer();
	shared_ptr<Player> FirstWith8Buildings = nullptr;
	shared_ptr<BuildingCard> RandomCard(vector<shared_ptr<BuildingCard>> cards);
	shared_ptr<CharacterCard> RandomCard(vector<shared_ptr<CharacterCard>> cards);
};