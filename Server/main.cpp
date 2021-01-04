#include "Server.h"
#include "Tank.h"
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
			Packet currentPacket = server.unprocessedPackets[0];
			char dataType = currentPacket.dataType;

			if (dataType == 't')
			{
				Tank tank;
				currentPacket.ExtractData(tank);
				
			}
			else
			{
				cout << "Invalid data type" << endl;
			}

			server.unprocessedPackets.erase(server.unprocessedPackets.begin());
		}
	}

	// pause the program
	cin.get();
}