#include "King.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include "Utility.h"
#include <string>

King::King(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
}

void King::BeginTurn()
{
	GetGoldForBuildings();
	game->SetNewKing(owner);
}

King::~King()
{
}
