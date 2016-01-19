#include "CharacterCard.h"
#include "Player.hpp"
#include "GameController.h"
#include "Machiavelli.h"

void CharacterCard::BeginTurn()
{
	if (robbed)
	{
		for(auto& character : game->getCharacters())
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
	socket.write(machiavelli::prompt);
	while (true)
	{
		if (owner->GetLastCommand() != "")
		{
			try {
				int choice = stoi(owner->GetLastCommand());
				owner->ResetLastCommand();
				if (choice >= 0 && choice <= amountOfChoices)
				{
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
						Action();
						break;
					case 4:
						return;
					case 5:
						GetGoldForBuildings();
						break;
					}
					ShowActions(amountOfChoices);
				}
			}
			catch (...)
			{
				socket.write("Wrong number.\r\n");
				socket.write(machiavelli::prompt);
			}
			socket.write(machiavelli::prompt);
		}
	}
}

void CharacterCard::ShowActions(int& amountOfChoices)
{
	auto& socket = owner->GetSocket();
	socket.write("Je bent nu de : " + name + "\r\n");
	owner->ShowInfo();
	socket.write("Maak een keuze : \r\n");
	socket.write("0. Bekijk goud en gebouwen van de tegenstander.\r\n");
	socket.write("1. Neem 2 goudstukken.\r\n");
	socket.write("2. Neem 2 gebouwenkaarten en leg er 1 af.\r\n");
	socket.write("3. Maak gebruik van de karaktereigenschap van de " + name + ".\r\n");
	socket.write("4. Beeindig je beurt.\r\n");
	amountOfChoices = 4;
	if (color != ColorEnum::NONE)
	{
		socket.write("5. Ontvang goudstukken voor gekleurde gebouwen.\r\n");
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
	socket.write(machiavelli::prompt);
	while (true)
	{
		try {
			if (owner->GetLastCommand() != "") {
				int choice = stoi(owner->GetLastCommand());
				if (choice == 0)
				{
					owner->AddCardToHand(card1);
				}
				else if (choice == 1)
				{
					owner->AddCardToHand(card2);
				}
				else 
				{
					socket.write("Kies 0 of 1.\r\n");
					socket.write(machiavelli::prompt);
				}
			}
		}
		catch (...)
		{
			socket.write("Wrong number.\r\n");
			socket.write(machiavelli::prompt);
		}
	}
	TurnBenefit = true;
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
