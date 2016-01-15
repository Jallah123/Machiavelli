#pragma once
#include "CharacterCard.h"
class Preacher :
	public CharacterCard
{
public:
	Preacher(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Preacher();
};

