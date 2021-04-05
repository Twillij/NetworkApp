#pragma once
#include "World.h"
#include "Tank.h"
#include <Client.h>

class Arena : public World
{
public:
	Arena();
	virtual ~Arena();

	vec3 borders = { 1280, 720, 0 };

	Client* client = nullptr;
	Tank* player = nullptr;

	vec3 GetRandomLocation();
	Tank::Colour GetRandomTankColour(bool removeColour = false);

	void JoinServer();

	virtual void Update(float deltaTime);

private:
	vector<Tank::Colour> availableTanks;
};
