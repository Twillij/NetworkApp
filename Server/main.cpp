#include "Server.h"
#include <iostream>

using std::cin;

int main()
{
	Server server;
	server.SetupListenSocket();
	server.ListenToClients();

	bool online = true; // status of server

	while (online)
	{
		// if there is an unprocessed pocket
		if (server.unprocessedPackets.size() > 0)
		{

			// shutdown server
			online = false;
		}
	}

	// pause the program
	cin.get();
}