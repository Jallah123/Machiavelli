#pragma once
#include "CharacterCard.h"
class Thief :
	public CharacterCard
{
public:
	Thief(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Thief();
};

