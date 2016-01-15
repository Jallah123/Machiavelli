#pragma once
#include "CharacterCard.h"
class Warlord :
	public CharacterCard
{
public:
	Warlord(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Warlord();
};

