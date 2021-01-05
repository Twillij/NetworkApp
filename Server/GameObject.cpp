#include "GameObject.h"
#include "World.h"
#include <glm/ext.hpp>

GameObject::~GameObject()
{
	delete texture;
}

unsigned int GameObject::GetObjectID()
{
	return objectID;
}

void GameObject::SetObjectID(unsigned int id)
{
	objectID = id;
}

World* GameObject::GetWorld()
{
	return world;
}

void GameObject::SetWorld(World* world)
{
	this->world = world;
}

mat3 GameObject::GetTransform()
{
	return globalTransform;
}

void GameObject::SetTransform(mat3 transform)
{
	localTransform = transform;
	UpdateTransform();
}


vec3 GameObject::GetLocation()
{
	return globalTransform[2];
}

void GameObject::SetLocation(vec3 location)
{
	localTransform[2] = location;
	UpdateTransform();
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
