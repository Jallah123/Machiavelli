#include "King.h"
#include "Player.hpp"
#include "GameController.h"
#include "Socket.h"
#include "Utility.h"
#include <string>

void King::Action(){ }

void King::BeginTurn()
{
	CharacterCard::BeginTurn();
	game->SetNewKing(owner);
}