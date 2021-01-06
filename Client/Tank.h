#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	Tank();
	~Tank() {}

	bool isPlayerControlled = false;

	float moveSpeed = 1000;

	virtual void Update(float deltaTime);
};
