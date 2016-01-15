#pragma once
#include "CharacterCard.h"
class King :
	public CharacterCard
{
public:
	King(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() override;
	virtual void Action() override;
	~King();
};

