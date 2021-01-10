#include "Tank.h"
#include <Input.h>
#include <iostream>

using namespace aie;

Tank::Colour Tank::GetColour()
{
	return colour;
}

void Tank::SetColour(Colour colour, bool loadTexture)
{
	this->colour = colour;

	if (loadTexture)
	{
		if (colour == Colour::GREEN)
		{
			LoadTexture("./textures/tankGreen.png");
		}
		else if (colour == Colour::BLUE)
		{
			LoadTexture("./textures/tankBlue.png");
		}
		else if (colour == Colour::ORANGE)
		{
			LoadTexture("./textures/tankOrange.png");
		}
		else if (colour == Colour::GRAY)
		{
			LoadTexture("./textures/tankGray.png");
		}
	}
}

void Tank::Update(float deltaTime)
{
	if (isPlayerControlled)
	{
		Input* input = Input::getInstance();
		Client* client = GetClient();

		if (input->isKeyDown(INPUT_KEY_W))
		{
			vec3 direction = GetForward();
			vec3 translation = direction * moveSpeed * deltaTime;

			if (client)
			{
				Packet moveForward;
				moveForward.dataType = 'w';
				moveForward.objectID = GetObjectID();
				moveForward.StoreData(translation);
				client->SendPacket(moveForward);
			}
		}

		if (input->isKeyDown(INPUT_KEY_S))
		{
			vec3 direction = -GetForward();
			vec3 translation = direction * moveSpeed * deltaTime;

			if (client)
			{
				Packet moveBackward;
				moveBackward.dataType = 's';
				moveBackward.objectID = GetObjectID();
				moveBackward.StoreData(translation);
				client->SendPacket(moveBackward);
			}
		}

		if (input->isKeyDown(INPUT_KEY_A))
		{
			float angle = turnSpeed * deltaTime;

			if (client)
			{
				Packet rotateLeft;
				rotateLeft.dataType = 'a';
				rotateLeft.objectID = GetObjectID();
				rotateLeft.StoreData(angle);
				client->SendPacket(rotateLeft);
			}
		}

		if (input->isKeyDown(INPUT_KEY_D))
		{
			float angle = -turnSpeed * deltaTime;

			if (client)
			{
				Packet rotateRight;
				rotateRight.dataType = 'd';
				rotateRight.objectID = GetObjectID();
				rotateRight.StoreData(angle);
				client->SendPacket(rotateRight);
			}
		}
	}
}
