#pragma once
#include <Renderer2D.h>
#include <Texture.h>

using aie::Renderer2D;
using aie::Texture;

class World;

class GameObject
{
public:
	GameObject() {}
	GameObject(World* world);
	~GameObject() {}

	void Draw(Renderer2D* renderer);

private:
	World* world = nullptr;
	Texture* texture = nullptr;
};