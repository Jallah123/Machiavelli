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

void GameController::addPlayer(shared_ptr<Player> player)
{
	players.push_back(player);
	if (players.size() == 1)
	{
		currentState = SETUP;
	}
}

shared_ptr<Player> GameController::GetOldestPlayer()
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
		buildingCards.emplace_back(CardFactory::Instance()->createBuildingCard(elements[0], ColorMap[elements[2]], stoi(elements[1])));
	}
}

shared_ptr<Player> GameController::GetOtherPlayer(shared_ptr<Player> self)
{
	for each (auto& player in players)
	{
		if (player != self)
			return player;
	}
}

void GameController::GiveStartingResources()
{
	for (auto& player : players)
	{
		player->SetGold(2);
		for (int i = 1; i <= 4; i++)
		{
			player->AddCardToHand(TakeCard());
		}
	}
}

void GameController::ChooseCharacters()
{
	// Discard random card
	auto& card = RandomCard(characterCards);
	card->Discard();
	CurrentPlayer->GetSocket().write("Game discarded: " + card->GetName() + "\r\n");

	// Let king pick a character
	CurrentPlayer->ChooseCharacter();
	CurrentPlayer = GetOtherPlayer(CurrentPlayer);

	// Let others choose
	bool done = false;
	while (!done)
	{		
		CurrentPlayer->ChooseCharacter();
		CurrentPlayer->DiscardCharacter();
		CurrentPlayer = GetOtherPlayer(CurrentPlayer);
		int count = 0;
		for (auto& character: characterCards)
		{
			if (character->IsDiscarded() || character->GetOwner() != nullptr)
			{
				count++;
			}
		}
		if (count == characterCards.size())
		{
			done = true;
		}
	}

	// Picking cards is done, give starting resources
	GiveStartingResources();
	StartGame();
}

void GameController::StartGame()
{
	currentState = RUNNING;
	while (currentState == RUNNING)
	{

	}
}

void GameController::HandleCommand(shared_ptr<Player> player, string cmd)
{
	if (cmd == "exit")
	{
		player->GetSocket().write("Bye!\r\n");
	}
}

void GameController::SwapCards(shared_ptr<Player> p, vector<shared_ptr<BuildingCard>> cards)
{
	int amountDiscarded = cards.size();
	vector<shared_ptr<BuildingCard>> newCards;
	for (int i = 0; i < amountDiscarded; i++)
	{
		newCards.push_back(TakeCard());
	}

	for each (auto card in cards)
	{
		buildingCards.push_back(card);
	}
}

void GameController::createCharacterCards()
{
	vector<vector<string>> characters = Parser::Parse("characters.txt");
	for (auto &elements : characters)
	{
		characterCards.emplace_back(CardFactory::Instance()->createCharacterCard(stoi(elements[0]), elements[1], ColorMap.at(elements[2]), shared_ptr<GameController>(this)));
	}
}

shared_ptr<BuildingCard> GameController::TakeCard()
{
	shared_ptr<BuildingCard> card = RandomCard(buildingCards);
	buildingCards.erase(find(buildingCards.begin(), buildingCards.end(), card));
	return card;
}

shared_ptr<CharacterCard> GameController::chooseCharacterCard(int card)
{
	if (card >= 0 && card < characterCards.size())
	{
		return characterCards.at(card);
	}
	return nullptr;
}

shared_ptr<BuildingCard> GameController::RandomCard(vector<shared_ptr<BuildingCard>> cards)
{
	int cardIndex = Utility::GetInstance()->RandomNumber(0, cards.size() - 1);
	return cards.at(cardIndex);
}

shared_ptr<CharacterCard> GameController::RandomCard(vector<shared_ptr<CharacterCard>> cards)
{
	int cardIndex = Utility::GetInstance()->RandomNumber(0, cards.size() - 1);
	return cards.at(cardIndex);
}