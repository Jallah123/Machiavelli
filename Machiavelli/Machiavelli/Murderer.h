#pragma once
#include "CharacterCard.h"

class Murderer :
	public CharacterCard
{
public:
	Murderer() {};
	~Murderer() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
};

