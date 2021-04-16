#include "ClientStartScreen.h"
#include <Input.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace aie;

ClientStartScreen::ClientStartScreen()
{
	serverAddrBox.pos = { 640, 450 };
	serverAddrBox.extents = { 350, 20 };
	serverPortBox.pos = { 640, 300 };
	serverPortBox.extents = { 350, 20 };
	confirmButton.pos = { 640, 150 };
	confirmButton.extents = { 75, 25 };
	strcat(confirmButton.text, "Confirm");

	currentTextBox = &serverAddrBox;
}

void ClientStartScreen::Update(float deltaTime)
{
	Input* input = Input::getInstance();
	vector<unsigned int> inputs = input->getPressedCharacters();

	for (int i = 0; i < inputs.size(); ++i)
	{
		strcat(currentTextBox->text, (char*)&inputs[i]);
		std::cout << (char)inputs[i] << std::endl;
	}

	if (input->wasKeyPressed(INPUT_KEY_BACKSPACE))
	{
		int len = strlen(currentTextBox->text);

		if (len)
		{
			memmove(currentTextBox->text + len - 1, currentTextBox->text + len, 1);
			std::cout << len << std::endl;
		}
	}

	if (input->wasMouseButtonPressed(INPUT_MOUSE_BUTTON_LEFT))
	{
		int mouseX = input->getMouseX();
		int mouseY = input->getMouseY();

		float boxLeft = serverAddrBox.pos.x - serverAddrBox.extents.x;
		float boxRight = serverAddrBox.pos.x + serverAddrBox.extents.x;
		float boxBot = serverAddrBox.pos.y - serverAddrBox.extents.y;
		float boxTop = serverAddrBox.pos.y + serverAddrBox.extents.y;

		if (mouseX > boxLeft &&
			mouseX < boxRight &&
			mouseY > boxBot &&
			mouseY < boxTop)
		{
			currentTextBox = &serverAddrBox;
		}

		boxLeft = serverPortBox.pos.x - serverPortBox.extents.x;
		boxRight = serverPortBox.pos.x + serverPortBox.extents.x;
		boxBot = serverPortBox.pos.y - serverPortBox.extents.y;
		boxTop = serverPortBox.pos.y + serverPortBox.extents.y;

		if (mouseX > boxLeft &&
			mouseX < boxRight &&
			mouseY > boxBot &&
			mouseY < boxTop)
		{
			currentTextBox = &serverPortBox;
		}

		boxLeft = confirmButton.pos.x - confirmButton.extents.x;
		boxRight = confirmButton.pos.x + confirmButton.extents.x;
		boxBot = confirmButton.pos.y - confirmButton.extents.y;
		boxTop = confirmButton.pos.y + confirmButton.extents.y;

		if (mouseX > boxLeft &&
			mouseX < boxRight &&
			mouseY > boxBot &&
			mouseY < boxTop)
		{
			
		}
	}
}

void ClientStartScreen::Draw(Renderer2D* renderer, Font* font)
{
	if (!renderer || !font)
		return;

	renderer->drawBox(serverAddrBox.pos.x, serverAddrBox.pos.y, serverAddrBox.extents.x * 2, serverAddrBox.extents.y * 2);
	renderer->drawBox(serverPortBox.pos.x, serverPortBox.pos.y, serverPortBox.extents.x * 2, serverPortBox.extents.y * 2);
	renderer->drawBox(confirmButton.pos.x, confirmButton.pos.y, confirmButton.extents.x * 2, confirmButton.extents.y * 2);
	renderer->drawText(font, "Server IP Address", serverAddrBox.pos.x - serverAddrBox.extents.x, serverAddrBox.pos.y + 32);
	renderer->drawText(font, "Server Port", serverPortBox.pos.x - serverPortBox.extents.x, serverPortBox.pos.y + 32);

	renderer->setRenderColour(0.75f, 0.75f, 0.75f);

	if (strlen(serverAddrBox.text) == 0)
	{
		renderer->drawText(font, "Default: localhost", serverAddrBox.pos.x - serverAddrBox.extents.x, serverAddrBox.pos.y - serverAddrBox.extents.y);
	}

	if (strlen(serverPortBox.text) == 0)
	{
		renderer->drawText(font, "Default: 27015", serverPortBox.pos.x - serverPortBox.extents.x, serverPortBox.pos.y - serverPortBox.extents.y);
	}

	renderer->setRenderColour(0, 0, 0);
	renderer->drawText(font, serverAddrBox.text, serverAddrBox.pos.x - serverAddrBox.extents.x, serverAddrBox.pos.y - serverAddrBox.extents.y);
	renderer->drawText(font, serverPortBox.text, serverPortBox.pos.x - serverPortBox.extents.x, serverPortBox.pos.y - serverPortBox.extents.y);
	renderer->drawText(font, confirmButton.text, confirmButton.pos.x - 65, confirmButton.pos.y - 15);
	renderer->setRenderColour(1, 1, 1);
}
