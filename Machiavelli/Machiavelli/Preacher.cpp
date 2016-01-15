#include "Preacher.h"

Preacher::Preacher(int _id, string _name, ColorEnum _color, shared_ptr<GameController> _game) : CharacterCard(_id, _name, _color, _game)
{
}

void Preacher::Action()
{
	GetGoldForBuildings();
}

Preacher::~Preacher()
{
}
