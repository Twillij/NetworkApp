#pragma once
#include <vector>
#include <Renderer2D.h>
#include <glm/vec3.hpp>

using aie::Renderer2D;
using glm::vec3;
using std::vector;

class GameObject;

class World
{
public:
	World() {}
	~World();

	void SpawnObject(GameObject* newObject, vec3 location = vec3(0));
	void Update(float deltaTime);
	void Draw(Renderer2D* renderer);

private:
	vector<GameObject*> worldObjects;
};