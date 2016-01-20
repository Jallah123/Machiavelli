//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

#include "Utility.h"
#include "GameController.h"
#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.hpp"
#include "Machiavelli.h"

static Sync_queue<ClientCommand> queue;

shared_ptr<Player> initializeNewPlayer(shared_ptr<Socket> client, shared_ptr<GameController> gameController)
{
	client->write("Welcome to Machiavelli! To quit, type 'quit'.\r\n");
	client->write("What's your name?\r\n");
	client->write(machiavelli::prompt);
	string name{ client->readline() };
	vector<string> splittedDate;
	int day = 0;
	int month = 0;
	int year = 0;

	while (day == 0 || month == 0 || year == 0)
	{
		splittedDate.clear();
		client->write("What's your birth date  (dd-mm-yyyy)\r\n");
		client->write(machiavelli::prompt);
		string date{ client->readline() };

		try
		{
			Utility::split(date, '-', splittedDate);
			if (splittedDate.size() != 3)
			{
				throw exception("");
			}
			day = stoi(splittedDate[0]);
			month = stoi(splittedDate[1]);
			year = stoi(splittedDate[2]);
		}
		catch (...)
		{
			*client << "Birthday not correct please try again. (dd-mm-yyyy)\r\n";
		}
	}

	shared_ptr<Player> player{ new Player{ name, day, month, year, client, gameController } };

	*client << "Welcome, " << name << ", have fun playing our game!\r\n" << machiavelli::prompt;
	return player;
}

void consume_command() // runs in its own thread
{
	try
	{
		while (true)
		{
			ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
			shared_ptr<Socket> client{ command.get_client() };
			shared_ptr<Player> player{ command.get_player() };
			try
			{
				// TODO handle command here
				//*client << player->getName() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
				player->SetLastCommand(command.get_cmd());
			}
			catch (const exception& ex)
			{
				cerr << "*** exception in consumer thread for player " << player->getName() << ": " << ex.what() << '\n';
				if (client->is_open()) 
				{
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
			catch (...)
			{
				cerr << "*** exception in consumer thread for player " << player->getName() << '\n';
				if (client->is_open()) 
				{
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
		}
	}
	catch (...) {
		cerr << "consume_command crashed\n";
	}
}

void handle_client(shared_ptr<Socket> client, shared_ptr<GameController> gameController) // this function runs in a separate thread
{
	try
	{
		shared_ptr<Player> player = initializeNewPlayer(client, gameController);
		gameController->addPlayer(player);
		while (true)
		{ // game loop
			try
			{
				if (gameController.get()->getState() == INITIALIZING)
				{
					client->write("Waiting for players...");
				}
				// read first line of request
				string cmd{ client->readline() };
				cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->getName() << "] " << cmd << '\n';

				gameController->HandleCommand(player, cmd);

				ClientCommand command{ cmd, client, player };
				queue.put(command);
			}
			catch (const exception& ex)
			{
				cerr << "*** exception in client handler thread for player " << player->getName() << ": " << ex.what() << '\n';
				if (client->is_open())
				{
					*client << "ERROR: " << ex.what() << "\r\n";
				}
			}
			catch (...)
			{
				cerr << "*** exception in client handler thread for player " << player->getName() << '\n';
				if (client->is_open())
				{
					client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
				}
			}
		}
		if (client->is_open()) client->close();
	}
	catch (...)
	{
		cerr << "handle_client crashed\n";
	}
}

int main(int argc, const char * argv[])
{
	// start command consumer thread
	thread consumer{ consume_command };

	// keep client threads here, so we don't need to detach them
	vector<thread> handlers;

	// create a server socket
	ServerSocket server{ machiavelli::tcp_port };

	// create gamecontroller
	shared_ptr<GameController> gameController = shared_ptr<GameController>(new GameController);
	while (true)
	{
		try
		{
			while (true)
			{
				// wait for connection from client; will create new socket
				while (gameController->getState() == INITIALIZING)
				{
					cerr << "server listening" << '\n';
					unique_ptr<Socket> client{ server.accept() };

					// communicate with client over new socket in separate thread
					thread handler{ handle_client, move(client), gameController };
					handlers.push_back(move(handler));
				}
				while (gameController->getState() == SETUP)
				{
					gameController->StartGame();
				}
			}
		}
		catch (const exception& ex)
		{
			cerr << ex.what() << ", resuming..." << '\n';
		}
		catch (...)
		{
			cerr << "problems, problems, but: keep calm and carry on!\n";
		}
	}
	return 0;
}