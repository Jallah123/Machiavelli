#pragma once
#include "CharacterCard.h"
class Warlord :
	public CharacterCard
{
public:
	Warlord() {};
	~Warlord() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
};