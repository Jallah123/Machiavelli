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
	while (true)
	{
		if (player->GetLastCommand() != "") {
			try 
			{
				number = stoi(player->GetLastCommand());
				if (number <= max && number >= min)
				{
					return number;
				}
			}
			catch (...)
			{
				player->GetSocket().write("Niet een geldig nummer.\r\n");
				player->GetSocket().write(machiavelli::prompt);
			}
		}
		if (player->GetLastCommand() == "cancel")
		{
			return -1;
		}
		player->ResetLastCommand();
		player->GetSocket().write(machiavelli::prompt);
	}
}

SocketUtil::SocketUtil()
{
}


SocketUtil::~SocketUtil()
{
}
