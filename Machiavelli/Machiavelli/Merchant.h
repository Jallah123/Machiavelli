#pragma once
#include "CharacterCard.h"
class Merchant :
	public CharacterCard
{
public:
	Merchant() {};
	~Merchant() {};
	virtual void BeginTurn();
	virtual void Action() override;
};

