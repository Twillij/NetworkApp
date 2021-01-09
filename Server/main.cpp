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

			// update the client that is trying to join the server
			if (dataType == 'J')
			{
				SOCKET sender = server.GetSocket(currentPacket.senderID);
				vector<GameObject*> tanks = arena.GetAllObjectsOfType(typeid(Tank));

				for (int i = 0; i < tanks.size(); ++i)
				{
					Packet spawnCommand;
					spawnCommand.dataType = 'T';
					spawnCommand.objectID = tanks[i]->GetObjectID();

					Packet setTransform;
					setTransform.dataType = 't';
					setTransform.objectID = spawnCommand.objectID;
					mat3 transform = tanks[i]->GetLocalTransform();
					setTransform.StoreData(transform);

					server.SendPacket(sender, spawnCommand);
					server.SendPacket(sender, setTransform);
				}
			}
			// spawn a new tank
			else if (dataType == 'T')
			{
				Tank* newTank = new Tank();
				newTank->SetObjectID(objectID);
				arena.SpawnObject(newTank, arena.GetRandomLocation());
				mat3 transform = newTank->GetLocalTransform();

				Packet spawnCommand;
				spawnCommand.dataType = 'T';
				spawnCommand.objectID = objectID++;
				//bool isPlayerControllable = true;
				//spawnCommand.StoreData(isPlayerControllable);

				Packet setTransform;
				setTransform.dataType = 't';
				setTransform.objectID = spawnCommand.objectID;
				setTransform.StoreData(transform);

				// send packets containing the tank data
				for (int i = 1; i < server.clients.fd_count; ++i)
				{
					server.SendPacket(server.clients.fd_array[i], spawnCommand);
					server.SendPacket(server.clients.fd_array[i], setTransform);
				}
			}
			// move a tank forward or backward
			else if (dataType == 'w' || dataType == 's')
			{
				Tank* tank = dynamic_cast<Tank*>(arena.GetWorldObject(currentPacket.objectID));

				if (tank)
				{
					vec3 translation;
					currentPacket.ExtractData(translation);
					tank->Translate(translation);
					mat3 transform = tank->GetLocalTransform();

					Packet setTransform;
					setTransform.dataType = 't';
					setTransform.objectID = currentPacket.objectID;
					setTransform.StoreData(transform);
					
					std::cout << "location:" << transform[2].x << ", " << transform[2].y << ", " << transform[2].z << std::endl;

					// send packets containing the tank data
					for (int i = 1; i < server.clients.fd_count; ++i)
					{
						server.SendPacket(server.clients.fd_array[i], setTransform);
					}
				}
			}
			// shut down server
			else if (dataType == 'x')
			{
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