#include "GameObject.h"
#include "World.h"
#include <glm/ext.hpp>

GameObject::GameObject(World* world)
{
	this->world = world;
}

GameObject::~GameObject()
{
	delete texture;
}

void GameObject::Draw(Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(texture, &globalTransform[0][0]);
}
