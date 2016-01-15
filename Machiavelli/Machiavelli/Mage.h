#pragma once
#include "CharacterCard.h"
class Mage :
	public CharacterCard
{
public:
	Mage(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game);
	virtual void BeginTurn() {};
	virtual void Action() override;
	~Mage();
private:
	void SwapCards();
	void DiscardCards();
};

