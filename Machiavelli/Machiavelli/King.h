#pragma once
#include "CharacterCard.h"
class King :
	public CharacterCard
{
public:
	King() {};
	~King() {};
	virtual void BeginTurn() override;
	virtual void Action() override;
};

