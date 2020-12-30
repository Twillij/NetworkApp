#include "Arena.h"
#include "Tank.h"

Arena::Arena()
{
	player = new Tank();
	SpawnObject(player);
}
