#pragma once
#include "World.h"
#include "Client.h"

class Tank;

class Arena : public World
{
public:
	Arena() {}
	~Arena() {}

	vec3 borders = { 1280, 720, 0 };

	Client* client = nullptr;
	Tank* player = nullptr;

	vec3 GetRandomLocation();
};
