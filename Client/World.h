#pragma once
#include <vector>

using std::vector;

class GameObject;

class World
{
public:
	World() {}
	~World();

	void SpawnObject();

private:
	vector<GameObject*> worldObjects;
};