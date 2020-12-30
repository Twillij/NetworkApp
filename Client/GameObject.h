#pragma once
#include <Renderer2D.h>
#include <Texture.h>
#include <glm/mat3x3.hpp>

using namespace aie;
using namespace glm;

class World;

class GameObject
{
public:
	GameObject() {}
	GameObject(World* world);
	~GameObject() {}

	void Draw(Renderer2D* renderer);

private:
	mat3 globalTransform = mat3(1);
	mat3 localTransform = mat3(1);
	World* world = nullptr;
	Texture* texture = nullptr;
};