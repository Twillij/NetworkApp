#define GLM_ENABLE_EXPERIMENTAL

#include "GameObject.h"
#include "World.h"
#include <glm/gtx/matrix_transform_2d.hpp>

GameObject::~GameObject()
{
	if (texture)
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

Client* GameObject::GetClient()
{
	return client;
}

void GameObject::SetClient(Client* client)
{
	this->client = client;
}

World* GameObject::GetWorld()
{
	return world;
}

void GameObject::SetWorld(World* world)
{
	this->world = world;
}

mat3 GameObject::GetLocalTransform()
{
	return localTransform;
}

void GameObject::SetLocalTransform(mat3 transform)
{
	localTransform = transform;
	UpdateTransform();
}

mat3 GameObject::GetGlobalTransform()
{
	return globalTransform;
}

vec3 GameObject::GetForward()
{
	return globalTransform[1];
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

void GameObject::LoadTexture(const char* filename)
{
	if (texture)
		texture->load(filename);
	else
		texture = new Texture(filename);
}

void GameObject::Translate(vec3 translation)
{
	localTransform[2] = localTransform[2] + translation;
	UpdateTransform();
}

void GameObject::Rotate(float deg)
{
	float rad = 2 * acosf(0) / 180 * deg;
	localTransform = rotate(localTransform, rad);
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
