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
	GameObject(World* world);
	~GameObject();

	void LoadTexture(const char* filename);

	vec3 GetLocation();
	void SetLocation(vec3 location);

	virtual void Update(float deltaTime) {}
	virtual void Draw(Renderer2D* renderer);

private:
	mat3 globalTransform = mat3(1);
	mat3 localTransform = mat3(1);
	World* world = nullptr;
	Texture* texture = nullptr;
	GameObject* parent = nullptr;
	vector<GameObject*> children;

	void UpdateTransform();
};