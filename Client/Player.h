#pragma once
#include "GameObject.h"
#include <Texture.h>

using aie::Texture;

class Player : public GameObject
{
public:
	Player() {}
	~Player() {}

private:
	Texture* texture = nullptr;
};