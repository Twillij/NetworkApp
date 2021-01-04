#include "Arena.h"
#include "Tank.h"
#include <time.h>

Arena::~Arena()
{
	delete client;
}

vec3 Arena::GetRandomLocation()
{
	vec3 location;

	srand(time(NULL));
	location.x = rand() % (int)borders.x;
	location.y = rand() % (int)borders.y;
	location.z = rand() % (int)borders.z;

	return location;
}

void Arena::JoinServer()
{
	if (!client)
	{
		// client setup
		client = new Client();
		client->ConnectToServer();
		client->StartServerThread();

		// request to create new tank
		Packet packet;
		packet.dataType = 't';
		client->SendPacket(packet);
	}
}

void Arena::Update(float deltaTime)
{
	// if there is an unprocessed pocket
	//while (client->unprocessedPackets.size() > 0)
	//{
	//	Packet currentPacket = client->unprocessedPackets[0];

	//	if (currentPacket.dataType == 't')
	//	{
	//		Tank newTank;
	//		currentPacket.ExtractData(newTank);
	//		SpawnObject(&newTank, newTank.GetLocation());
	//	}
	//	else
	//	{
	//		cout << "Invalid data type" << endl;
	//	}

	//	client->unprocessedPackets.pop_front();
	//}
	
	if (client->unprocessedPackets.size() > 0)
	{
		cout << "processing packet" << endl;
		Packet currentPacket = client->unprocessedPackets[0];

		if (currentPacket.dataType == 't')
		{
			int test = 0;
			currentPacket.ExtractData(test);
			cout << "test: " << test << endl;
			//Tank newTank;
			//currentPacket.ExtractData(newTank);
			//SpawnObject(&newTank, newTank.GetLocation());
		}
		else
		{
			cout << "Invalid data type" << endl;
		}

		client->unprocessedPackets.pop_front();
	}

	World::Update(deltaTime);
}
