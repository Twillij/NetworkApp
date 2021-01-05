#pragma once
#include <vector>
#include <Renderer2D.h>
#include <Texture.h>
#include <glm/mat3x3.hpp>
#include <glm/vec3.hpp>

using aie::Renderer2D;
using aie::Texture;
using std::vector;
using namespace glm;

class World;

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject();

	unsigned int GetObjectID();
	void SetObjectID(unsigned int id);

	World* GetWorld();
	void SetWorld(World* world);

	mat3 GetTransform();
	void SetTransform(mat3 transform);

	vec3 GetLocation();
	void SetLocation(vec3 location);

	void LoadTexture(const char* filename);

	virtual void Update(float deltaTime) {}
	virtual void Draw(Renderer2D* renderer);

private:
	unsigned int objectID = 0;
	mat3 globalTransform = mat3(1);
	mat3 localTransform = mat3(1);
	World* world = nullptr;
	Texture* texture = nullptr;
	GameObject* parent = nullptr;
	vector<GameObject*> children;

	void UpdateTransform();
};
