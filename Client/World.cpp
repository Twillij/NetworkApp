#include "World.h"
#include "GameObject.h"
#include <iostream>

World::~World()
{
	for (int i = 0; i < worldObjects.size(); ++i)
		delete worldObjects[i];
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
