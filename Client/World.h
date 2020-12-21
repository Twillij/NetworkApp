#pragma once
#include <vector>

using std::vector;

class GameObject;

class World
{
public:
	World() {}
	~World() {}

	vector<GameObject*> worldObjects;
};