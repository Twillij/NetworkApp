#include "Server.h"
#include "Tank.h"
#include "Arena.h"
#include <iostream>

using namespace std;

int main()
{
	Server server;
	server.SetupListenSocket();
	server.StartListeningThread();

	bool online = true; // status of server
	Arena arena;

	while (online)
	{
		// if there is an unprocessed pocket
		if (server.unprocessedPackets.size() > 0)
		{
			Packet currentPacket = server.unprocessedPackets[0];
			char dataType = currentPacket.dataType;

			if (dataType == 'I')
			{
				// request for ID
				cout << "sender ID: " << currentPacket.senderID << endl;
			}
			else if (dataType == 't')
			{
				// spawn a new tank
				Tank* tank = new Tank();
				arena.SpawnObject(tank, arena.GetRandomLocation());
				int test = 420;
				// send a packet containing the tank data
				currentPacket.StoreData(test);
				for (int i = 1; i < server.clients.fd_count; ++i)
				{
					server.SendPacket(server.clients.fd_array[i], currentPacket);
				}
			}
			else if (dataType == 'x')
			{
				// shut down server
				online = false;
			}
			else
			{
				cout << "Invalid data type" << endl;
			}

			server.unprocessedPackets.pop_front();
		}
	}

	// pause the program
	cin.get();
}