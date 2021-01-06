#include "Tank.h"
#include <Input.h>

using namespace aie;

Tank::Tank()
{
	LoadTexture("./textures/tankGreen.png");
}

void Tank::Update(float deltaTime)
{
	if (isPlayerControlled)
	{
		Input* input = Input::getInstance();

		if (input->isKeyDown(INPUT_KEY_W))
		{

		}

		if (input->isKeyDown(INPUT_KEY_S))
		{

		}
	}
}
