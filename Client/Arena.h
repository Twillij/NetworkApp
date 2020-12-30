#pragma once
#include "World.h"

class Tank;

class Arena : public World
{
public:
	Arena();
	~Arena() {}

	Tank* player = nullptr;
};
