#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	Tank();
	~Tank() {}

	bool isPlayerControlled = false;

	virtual void Update(float deltaTime);
};
