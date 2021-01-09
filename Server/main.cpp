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
			SOCKET sender = server.GetSocket(currentPacket.senderID);
			char dataType = currentPacket.dataType;

			// update the client that is trying to join the server
			if (dataType == 'J')
			{
				
				vector<GameObject*> tanks = arena.GetAllObjectsOfType(typeid(Tank));

				for (int i = 0; i < tanks.size(); ++i)
				{
					Packet spawnObject;
					spawnObject.dataType = 'T';
					spawnObject.objectID = tanks[i]->GetObjectID();

					Packet setTransform;
					setTransform.dataType = 't';
					setTransform.objectID = spawnObject.objectID;
					mat3 transform = tanks[i]->GetLocalTransform();
					setTransform.StoreData(transform);

					server.SendPacket(sender, spawnObject);
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

				Packet spawnTank;
				spawnTank.dataType = 'T';
				spawnTank.objectID = objectID++;

				Packet setTransform;
				setTransform.dataType = 't';
				setTransform.objectID = spawnTank.objectID;
				setTransform.StoreData(transform);

				// send packets containing the tank data
				for (int i = 1; i < server.clients.fd_count; ++i)
				{
					if (server.clients.fd_array[i] == sender)
					{
						Packet spawnPlayer = spawnTank;
						bool isPlayerControllable = true;
						spawnPlayer.StoreData(isPlayerControllable);
						server.SendPacket(sender, spawnPlayer);
					}
					else
					{
						server.SendPacket(server.clients.fd_array[i], spawnTank);
					}
					
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