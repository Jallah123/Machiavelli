#pragma once
#include "CharacterCard.h"
class Merchant :
	public CharacterCard
{
public:
	Merchant(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn();
	virtual void Action() override;
	~Merchant();
};

