#include "Arena.h"
#include "Tank.h"
#include <time.h>

Arena::Arena()
{
	availableTanks.push_back(Tank::Colour::GREEN);
	availableTanks.push_back(Tank::Colour::BLUE);
	availableTanks.push_back(Tank::Colour::ORANGE);
	availableTanks.push_back(Tank::Colour::GRAY);
}

Arena::~Arena()
{
	if (client)
	{
		Packet goOffline;
		goOffline.dataType = 'x';
		client->SendPacket(goOffline);
		delete client;
	}
}

vec3 Arena::GetRandomLocation()
{
	vec3 location;

	srand(time(NULL));
	location.x = (borders.x) ? rand() % (int)borders.x : 0;
	location.y = (borders.y) ? rand() % (int)borders.y : 0;
	location.z = (borders.z) ? rand() % (int)borders.z : 0;

	return location;
}

Tank::Colour Arena::GetRandomTankColour(bool removeColour)
{
	srand(time(NULL));
	int index = rand() % availableTanks.size();
	Tank::Colour result = availableTanks[index];

	if (removeColour)
		availableTanks.erase(availableTanks.begin() + index);

	return result;
}

void Arena::JoinServer()
{
	if (!client)
	{
		// client setup
		client = new Client();
		client->ConnectToServer();
		client->StartServerThread();

		// request to join server
		Packet joinServer;
		joinServer.dataType = 'J';
		client->SendPacket(joinServer);

		// request to create new tank
		Packet createTank;
		createTank.dataType = 'T';
		client->SendPacket(createTank);
	}
}

void Arena::Update(float deltaTime)
{
	while (client->unprocessedPackets.size() > 0)
	{
		Packet currentPacket = client->unprocessedPackets[0];

		if (currentPacket.dataType == 'T')
		{
			Tank* newTank = new Tank();
			currentPacket.ExtractData(newTank->isPlayerControlled);

			if (!player && newTank->isPlayerControlled)
			{
				player = newTank;
			}
			
			newTank->SetObjectID(currentPacket.objectID);
			newTank->SetClient(client);
			SpawnObject(newTank);
		}
		else if (currentPacket.dataType == 't')
		{
			mat3 transform;
			currentPacket.ExtractData(transform);
			GameObject* targetObject = GetWorldObject(currentPacket.objectID);

			if (targetObject)
				targetObject->SetLocalTransform(transform);
		}
		else if (currentPacket.dataType == 'c')
		{
			Tank::Colour colour;
			currentPacket.ExtractData(colour);
			Tank* targetObject = dynamic_cast<Tank*>(GetWorldObject(currentPacket.objectID));

			if (targetObject)
				targetObject->SetColour(colour);
		}
		else
		{
			cout << "Invalid data type" << endl;
		}

		client->unprocessedPackets.pop_front();
	}

	World::Update(deltaTime);
}
