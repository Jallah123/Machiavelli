#pragma once
#include "CharacterCard.h"
class Mage :
	public CharacterCard
{
public:
	Mage() {};
	~Mage() {};
	virtual void BeginTurn() {};
	virtual void Action() override;
private:
	void SwapCards();
	void DiscardCards();
};

