#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	Tank();
	~Tank() {}

	bool isPlayerControlled = false;

	float moveSpeed = 150;
	float turnSpeed = 100;

	virtual void Update(float deltaTime);
};
