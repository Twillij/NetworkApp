#include "World.h"
#include "GameObject.h"

World::~World()
{
	for (int i = 0; i < worldObjects.size(); ++i)
		delete worldObjects[i];
}

void World::SpawnObject()
{
	GameObject* newObject = new GameObject(this);
	worldObjects.push_back(newObject);
}
