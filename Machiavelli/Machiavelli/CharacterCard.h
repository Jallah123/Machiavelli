#pragma once
#include "Card.h"
#include <memory>

class Player;
class GameController;
class CharacterCard :
	public Card
{
public:
	CharacterCard(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : Card(_name, _color), id(_id), game(_game) {};
	virtual void BeginTurn() = 0;
	virtual void Action() = 0;
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
	int maxBuildings = 1;
	shared_ptr<Player> owner;
	shared_ptr<GameController> game;
};

