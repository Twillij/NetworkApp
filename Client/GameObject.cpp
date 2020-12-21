#include "GameObject.h"
#include "World.h"

GameObject::GameObject(World* world)
{
	this->world = world;
}

void GameObject::Draw(Renderer2D* renderer)
{
	//renderer->drawSpriteTransformed3x3(texture, )
}
