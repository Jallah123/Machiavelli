#include "Architect.h"
#include "Player.hpp"
#include "GameController.h"

void Architect::Action()
{
	owner->AddCardToHand(game->TakeCard());
	owner->AddCardToHand(game->TakeCard());
	ActionDone = true;
}