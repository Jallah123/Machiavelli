#include "GameController.h"
#include "Parser.h"

GameController::GameController()
{
	currentState = INITIALIZING;
	createBuildingCards();
	createCharacterCards();
}

GameController::~GameController()
{

}

void GameController::createBuildingCards()
{
	vector<vector<string>> buildings = Parser::Parse("buildings.txt");
	for (auto &elements : buildings)
	{
		buildingCards.push_back(unique_ptr<BuildingCard>(new BuildingCard(elements[0], ColorMap[elements[2]], stoi(elements[1]))));
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