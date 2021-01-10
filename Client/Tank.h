#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	Tank() {}
	~Tank() {}

	enum class Colour
	{
		GREEN,
		BLUE,
		ORANGE,
		GRAY
	};

	bool isPlayerControlled = false;
	float moveSpeed = 150;
	float turnSpeed = 100;

	Colour GetColour();
	void SetColour(Colour colour, bool loadTexture = true);

	virtual void Update(float deltaTime);

private:
	Colour colour;
};
