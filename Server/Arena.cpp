#include "Arena.h"
#include "Tank.h"
#include <time.h>

Arena::Arena()
{
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
	if (client)
	{
		player = new Tank();
		SpawnObject(player, GetRandomLocation());

		Packet packet;
		packet.dataType = 't';
		packet.StoreData(*player);

		client->SendPacket(packet);
	}
}
