#include "GameController.h"
#include "Parser.h"
#include "Utility.h"

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
}

void GameController::createBuildingCards()
{
	vector<vector<string>> buildings = Parser::Parse("buildings.txt");
	for (auto &elements : buildings)
	{
		buildingCards.push_back(CardFactory::createBuildingCard(elements[0], ColorMap[elements[2]], stoi(elements[1])));
	}
}

void GameController::createCharacterCards()
{
	vector<vector<string>> characters = Parser::Parse("characters.txt");
	for (auto &elements : characters)
	{
		characterCards.push_back(CardFactory::createCharacterCard(stoi(elements[0]), elements[1], ColorMap.at(elements[2])));
	}
}

unique_ptr<BuildingCard> GameController::takeCard()
{
	int card = Utility::GetInstance()->RandomNumber(0, buildingCards.size()-1);
	return move(buildingCards.at(card));
}

unique_ptr<CharacterCard> GameController::chooseCharacterCard(int card)
{
	if (card >= 0 && card < characterCards.size())
	{
		return move(characterCards.at(card));
	}
	return nullptr;
}