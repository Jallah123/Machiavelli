#pragma once
#include "CharacterCard.h"
class Thief :
	public CharacterCard
{
public:
	Thief() {};
	~Thief() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
};

