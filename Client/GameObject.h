#pragma once

class World;

class GameObject
{
public:
	GameObject() {}
	GameObject(World* world);
	~GameObject() {}

private:
	World* world = nullptr;
};