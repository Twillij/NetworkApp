#include "Server.h"
#include <iostream>

using namespace std;

int main()
{
	Server server;
	server.SetupListenSocket();
	server.StartListeningThread();

	bool online = true; // status of server

	while (online)
	{
		// if there is an unprocessed pocket
		if (server.unprocessedPackets.size() > 0)
		{
			cout << "works" << endl;

			// shutdown server
			online = false;
		}
	}

	// pause the program
	cin.get();
}