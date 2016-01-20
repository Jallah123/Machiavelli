#pragma once
#include "CharacterCard.h"
#include "GameController.h"

class King :
	public CharacterCard
{
public:
	King() {};
	~King() {};
	virtual void BeginTurn() override;
	virtual void Action() override;
	void SetOwner(shared_ptr<Player> player) { owner = player; game->SetNewKing(player); } ;
};