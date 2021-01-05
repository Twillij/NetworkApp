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
	unsigned int objectID = 0;

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
			else if (dataType == 'T')
			{
				// spawn a new tank
				Tank* newTank = new Tank();
				newTank->SetObjectID(objectID);
				arena.SpawnObject(newTank, arena.GetRandomLocation());

				Packet spawnCommand;
				spawnCommand.dataType = 'T';
				spawnCommand.objectID = objectID++;

				Packet setTransform;
				setTransform.dataType = 't';
				setTransform.objectID = spawnCommand.objectID;
				mat3 transform = newTank->GetTransform();
				setTransform.StoreData(transform);

				// send packets containing the tank data
				for (int i = 1; i < server.clients.fd_count; ++i)
				{
					server.SendPacket(server.clients.fd_array[i], spawnCommand);
					server.SendPacket(server.clients.fd_array[i], setTransform);
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