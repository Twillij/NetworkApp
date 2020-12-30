#pragma once
#include <vector>
#include <Renderer2D.h>

using aie::Renderer2D;
using std::vector;

class GameObject;

class World
{
public:
	World() {}
	~World();

	void SpawnObject(GameObject* newObject = nullptr);
	void Update(float deltaTime);
	void Draw(Renderer2D* renderer);

private:
	vector<GameObject*> worldObjects;
};