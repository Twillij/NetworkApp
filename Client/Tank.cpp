#include "Tank.h"
#include <Input.h>
#include <iostream>

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
