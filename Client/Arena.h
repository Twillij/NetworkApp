#pragma once
#include "World.h"
#include "Server.h"

class Tank;

class Arena : public World
{
public:
	Arena();
	~Arena() {}

	Server* server = nullptr;
	Tank* player = nullptr;

	void JoinServer(Server* server);
};
