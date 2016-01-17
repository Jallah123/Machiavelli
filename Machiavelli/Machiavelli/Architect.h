#pragma once
#include "CharacterCard.h"
class Architect :
	public CharacterCard
{
public:
	Architect() { maxBuildings = 3; };
	~Architect() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
};

