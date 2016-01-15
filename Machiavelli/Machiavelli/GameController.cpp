#include "GameController.h"
#include "Parser.h"
#include "Utility.h"
#include <string>

GameController::GameController()
{
	currentState = INITIALIZING;
	createBuildingCards();
	createCharacterCards();
}

GameController::~GameController()
{

}

shared_ptr<Player> GameController::getOldestPlayer()
{
	// Calculate oldest player
	auto age = players.at(0).get()->getAge();
	int daysP1 = age.tm_mday + age.tm_mon * 31 + age.tm_year * 365;
	auto player2Age = players.at(1).get()->getAge();
	int daysP2 = player2Age.tm_mday + player2Age.tm_mon * 31 + player2Age.tm_year * 365;
	return (daysP1 <= daysP2) ? players.at(0) : players.at(1);
}


void GameController::createBuildingCards()
{
	vector<vector<string>> buildings = Parser::Parse("buildings.txt");
	for (auto &elements : buildings)
	{
		buildingCards.emplace_back(move(CardFactory::createBuildingCard(elements[0], ColorMap[elements[2]], stoi(elements[1]))));
	}
}

void GameController::createCharacterCards()
{
	vector<vector<string>> characters = Parser::Parse("characters.txt");
	for (auto &elements : characters)
	{
		characterCards.emplace_back(move(CardFactory::createCharacterCard(stoi(elements[0]), elements[1], ColorMap.at(elements[2]))));
	}
}
/*
shared_ptr<BuildingCard> GameController::takeCard()
{
	int cardIndex = Utility::GetInstance()->RandomNumber(0, buildingCards.size()-1);
	auto card = buildingCards.at(cardIndex);
	buildingCards.erase(cardIndex);
	return t;
}

shared_ptr<CharacterCard> GameController::chooseCharacterCard(int card)
{
	if (card >= 0 && card < characterCards.size())
	{
		return move(characterCards.at(card));
	}
	return nullptr;
}
*/
