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

void GameObject::LoadTexture(const char* filename)
{
	if (texture)
		texture->load(filename);
	else
		texture = new Texture(filename);
}

vec3 GameObject::GetLocation()
{
	return globalTransform[2];
}

void GameObject::SetLocation(vec3 location)
{
	localTransform[2] = location;
}

void GameObject::Draw(Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(texture, &globalTransform[0][0]);
}

void GameObject::UpdateTransform()
{
	globalTransform = (parent) ? globalTransform * localTransform : localTransform;

	for (int i = 0; i < children.size(); ++i)
		children[i]->UpdateTransform();
}
