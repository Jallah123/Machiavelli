#pragma once
#include "CharacterCard.h"
class Architect :
	public CharacterCard
{
public:
	Architect(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Architect();
};

