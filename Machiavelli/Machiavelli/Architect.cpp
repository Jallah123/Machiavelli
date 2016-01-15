#include "Architect.h"
#include "Player.hpp"
#include "GameController.h"

Architect::Architect(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
	maxBuildings = 3;
}

void Architect::Action()
{
	owner->AddCardToHand(game->takeCard());
	owner->AddCardToHand(game->takeCard());
	ActionDone = true;
}

Architect::~Architect()
{
}
