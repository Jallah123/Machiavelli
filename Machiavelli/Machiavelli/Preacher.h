#pragma once
#include "CharacterCard.h"
class Preacher :
	public CharacterCard
{
public:
	Preacher() {};
	~Preacher() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
};

