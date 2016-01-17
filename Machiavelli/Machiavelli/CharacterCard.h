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
	virtual void BeginTurn() = 0;
	virtual void Action() = 0;
	void GetGoldForBuildings();
	void SetOwner(shared_ptr<Player> p) { owner = p; };
	int GetId() { return id; };
	void Kill() { alive = false; };
	void Rob() { robbed = true; };
	bool IsAlive() { return alive; };
	bool IsRobbed() { return robbed; };
protected:
	int id;
	bool alive = true;
	bool robbed = false;
	bool ActionDone = false;
	bool GoldReceived = false;
	int maxBuildings = 1;
	shared_ptr<Player> owner;
	shared_ptr<GameController> game;
};

