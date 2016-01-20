#include "CharacterCard.h"
#include "Player.hpp"
#include "GameController.h"
#include "Machiavelli.h"
#include "SocketUtil.h"

void CharacterCard::BeginTurn()
{
	if (robbed)
	{
		for (auto& character : game->getCharacters())
		{
			// get thief
			if (character->GetId() == 2)
			{
				character->GetOwner()->AddGold(owner->GetGold());
			}
		}
		owner->GetSocket().write("You got robbed, you lost " + to_string(owner->GetGold()) + " gold. \r\n");
		owner->SetGold(0);
	}
}

void CharacterCard::PlayTurn()
{
	int amountOfChoices;
	ShowActions(amountOfChoices);
	auto& socket = owner->GetSocket();
	while (true)
	{
		int choice = SocketUtil::GetNumber(owner, amountOfChoices);
		owner->ResetLastCommand();

		switch (choice)
		{
		case 0:
			socket.write(game->GetOtherPlayer(owner)->GetInfo());
			break;
		case 1:
			GetTurnGold();
			break;
		case 2:
			GetTurnBuildings();
			break;
		case 3:
			BuildBuilding();
			break;
		case 4:
			if (ActionDone)
			{
				socket.write("Je hebt je actie al uitgevoerd.");
				break;
			}
			Action();
			break;
		case 5:
			return;
		case 6:
			GetGoldForBuildings();
			break;
		}
		ShowActions(amountOfChoices);
		owner->ResetLastCommand();

		socket.write(machiavelli::prompt);
	}
}

void CharacterCard::BuildBuilding()
{
	auto& socket = owner->GetSocket();
	int index = 0;
	for (auto& building : owner->GetHand())
	{
		socket.write(to_string(index) + ". " + building->GetInfo());
		index++;
	}
	int choice = SocketUtil::GetNumber(owner, index);
	shared_ptr<BuildingCard> card = owner->GetHand().at(choice);
	if (choice == -1 || card->GetCost() > owner->GetGold() || buildBuildings >= maxBuildings)
	{
		return;
	}
	buildBuildings++;
	owner->BuildBuilding(card);
	if (owner->GetPlayedCards().size() == 8)
	{
		game->Finish(owner);
	}
}

void CharacterCard::ShowActions(int& amountOfChoices)
{
	auto& socket = owner->GetSocket();
	socket.write("\r\n\r\n\r\n");
	socket.write("Je bent nu de : " + name + "\r\n");
	owner->ShowInfo();
	socket.write("Maak een keuze : \r\n");
	socket.write("0. Bekijk goud en gebouwen van de tegenstander.\r\n");
	socket.write("1. Neem 2 goudstukken.\r\n");
	socket.write("2. Neem 2 gebouwenkaarten en leg er 1 af.\r\n");
	socket.write("3. Bouw een gebouw.\r\n");
	socket.write("4. Maak gebruik van de karaktereigenschap van de " + name + ".\r\n");
	socket.write("5. Beeindig je beurt.\r\n");
	amountOfChoices = 5;
	if (color != ColorEnum::NONE)
	{
		socket.write("6. Ontvang goudstukken voor gekleurde gebouwen.\r\n");
		amountOfChoices++;
	}
}

void CharacterCard::GetTurnBuildings()
{
	if (TurnBenefit)
	{
		owner->GetSocket().write("Je hebt al goudstukken of bouwkaarten ontvangen.\r\n");
		return;
	}

	auto& card1 = game->TakeCard();
	auto& card2 = game->TakeCard();
	auto& socket = owner->GetSocket();
	socket.write("Kies 1 van de 2 volgende : \r\n");
	socket.write("0. " + card1->GetInfo());
	socket.write("1. " + card2->GetInfo());

	int choice = SocketUtil::GetNumber(owner, 1);
	if (choice == 0)
	{
		owner->AddCardToHand(card1);
	}
	else if (choice == 1)
	{
		owner->AddCardToHand(card2);
	}

	TurnBenefit = true;
}

void CharacterCard::Reset()
{
	alive = true;
	robbed = false;
	ActionDone = false;
	GoldReceived = false;
	TurnBenefit = false;
	discarded = false;
	buildBuildings = 0;
	if (owner != nullptr)
	{
		owner = nullptr;
	}
}

void CharacterCard::GetTurnGold()
{
	if (TurnBenefit)
	{
		owner->GetSocket().write("Je hebt al goudstukken of bouwkaarten ontvangen.\r\n");
		return;
	}
	owner->AddGold(2);
	owner->GetSocket().write("Je ontvangt 2 goudstukken, je hebt er nu " + to_string(owner->GetGold()));
	TurnBenefit = true;
}

void CharacterCard::GetGoldForBuildings()
{
	if (GoldReceived)
	{
		owner->GetSocket().write("Je hebt al goudstukken gekregen.\r\n");
		return;
	}
	for each (auto& card in owner->GetPlayedCards())
	{
		if (card->GetColor() == GetColor())
		{
			owner->GetSocket().write("Je ontvangt 1 goudstuk voor " + card->GetName() + " .\n");
			owner->AddGold(1);
		}
	}
	GoldReceived = true;
}
