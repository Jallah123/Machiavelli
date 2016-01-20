#include "SocketUtil.h"
#include "Player.hpp"
#include "Machiavelli.h"

int SocketUtil::GetNumber(shared_ptr<Player> player, int max, int min)
{
	if (max < min)
	{
		return -1;
	}
	int number = -1;
	player->GetSocket().write(machiavelli::prompt);
	player->ResetLastCommand();
	while (true)
	{
		if (player->GetLastCommand() != "") {
			try
			{
				number = stoi(player->GetLastCommand());
				if (number <= max && number >= min)
				{
					player->ResetLastCommand();
					return number;
				}
				else 
				{
					player->GetSocket().write("Number not in range.\r\n");
					player->GetSocket().write(machiavelli::prompt);
				}
			}
			catch (...)
			{
				player->GetSocket().write("Niet een geldig nummer.\r\n");
				player->GetSocket().write(machiavelli::prompt);
			}
			player->ResetLastCommand();
		}
		if (player->GetLastCommand() == "cancel")
		{
			player->ResetLastCommand();
			return -1;
		}
	}
}

SocketUtil::SocketUtil()
{
}


SocketUtil::~SocketUtil()
{
}
