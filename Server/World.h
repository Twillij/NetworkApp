#pragma once
#include <vector>
#include <typeinfo>
#include <Font.h>
#include <Renderer2D.h>
#include <glm/vec3.hpp>

using aie::Font;
using aie::Renderer2D;
using glm::vec3;
using std::vector;

class GameObject;

class World
{
public:
	World() {}
	virtual ~World();

	int GetObjectCount();
	GameObject* GetObjectList();
	GameObject* GetWorldObject(unsigned int id);

	template <class T>
	vector<GameObject*> GetAllObjectsOfType(T* objectPtr);

	void SpawnObject(GameObject* newObject, vec3 location = vec3(0));

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer, Font* font);

private:
	vector<GameObject*> worldObjects;
};

template<class T>
inline vector<GameObject*> World::GetAllObjectsOfType(T* objectPtr)
{
	vector<GameObject*> result;

	for (int i = 0; i < worldObjects.size(); ++i)
		if (dynamic_cast<T*>(worldObjects[i]))
			result.push_back(worldObjects[i]);

	return result;
}
