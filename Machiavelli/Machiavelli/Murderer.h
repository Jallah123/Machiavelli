#pragma once
#include "CharacterCard.h"

class Murderer :
	public CharacterCard
{
public:
	Murderer(int _id, string _name, ColorEnum _color);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Murderer();
};

