#include "World.h"
#include "GameObject.h"
#include <iostream>

World::~World()
{
	for (int i = 0; i < worldObjects.size(); ++i)
		delete worldObjects[i];
}

int World::GetObjectCount()
{
	return worldObjects.size();
}

GameObject* World::GetObjectList()
{
	return worldObjects[0];
}

GameObject* World::GetWorldObject(unsigned int id)
{
	for (int i = 0; i < worldObjects.size(); ++i)
		if (worldObjects[i]->GetObjectID() == id)
			return worldObjects[i];

	return nullptr;
}

vector<GameObject*> World::GetAllObjectsOfType(const type_info& objectType)
{
	vector<GameObject*> result;

	for (int i = 0; i < worldObjects.size(); ++i)
		if (typeid(worldObjects[i]) == objectType)
			result.push_back(worldObjects[i]);

	return result;
}

void World::SpawnObject(GameObject* newObject, vec3 location)
{
	newObject = (newObject) ? newObject : new GameObject();
	newObject->SetWorld(this);
	newObject->SetLocation(location);

	worldObjects.push_back(newObject);
}

void World::Update(float deltaTime)
{
	for (int i = 0; i < worldObjects.size(); ++i)
		worldObjects[i]->Update(deltaTime);
}

void World::Draw(Renderer2D* renderer)
{
	for (int i = 0; i < worldObjects.size(); ++i)
		worldObjects[i]->Draw(renderer);
}
