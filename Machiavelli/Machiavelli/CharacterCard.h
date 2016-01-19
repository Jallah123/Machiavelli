#pragma once
#include "Card.h"
#include <memory>

class Player;
class GameController;
class CharacterCard :
	public Card
{
public:
	CharacterCard() {};
	void Initialize(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game)
	{
		id = _id;
		name = _name;
		color = _color;
		game = _game;
	}
	virtual void BeginTurn();
	void PlayTurn();
	void ShowActions(int& amountOfChoices);
	void EndTurn();
	virtual void Action() = 0;
	void GetGoldForBuildings();
	void SetOwner(shared_ptr<Player> p) { owner = p; };
	shared_ptr<Player> GetOwner() { return owner; };
	int GetId() { return id; };
	void GetTurnGold();
	void GetTurnBuildings();
	void Kill() { alive = false; };
	void Rob() { robbed = true; };
	void Discard() { discarded = true; };
	bool IsAlive() { return alive; };
	bool IsRobbed() { return robbed; };
	bool IsDiscarded() { return discarded; };
protected:
	int id;
	bool alive = true;
	bool robbed = false;
	bool ActionDone = false;
	bool GoldReceived = false;
	bool TurnBenefit = false;
	bool discarded = false; 
	int maxBuildings = 1;
	shared_ptr<Player> owner = nullptr;
	shared_ptr<GameController> game;
};

