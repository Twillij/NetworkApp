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
	serverPortBox.pos = { 640, 210 };
	serverPortBox.extents = { 350, 20 };

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
}

void ClientStartScreen::Draw(Renderer2D* renderer, Font* font)
{
	if (!renderer || !font)
		return;

	renderer->drawText(font, "Server IP Address", serverAddrBox.pos.x - serverAddrBox.extents.x, serverAddrBox.pos.y + 32);
	renderer->drawText(font, "Server Port", serverPortBox.pos.x - serverPortBox.extents.x, serverPortBox.pos.y + 32);
	renderer->drawBox(serverAddrBox.pos.x, serverAddrBox.pos.y, serverAddrBox.extents.x * 2, serverAddrBox.extents.y * 2);
	renderer->drawBox(serverPortBox.pos.x, serverPortBox.pos.y, serverPortBox.extents.x * 2, serverPortBox.extents.y * 2);

	renderer->setRenderColour(0, 0, 0);
	renderer->drawText(font, serverAddrBox.text, serverAddrBox.pos.x - serverAddrBox.extents.x, serverAddrBox.pos.y - serverAddrBox.extents.y);
	renderer->drawText(font, serverPortBox.text, serverPortBox.pos.x - serverPortBox.extents.x, serverPortBox.pos.y - serverPortBox.extents.y);
	renderer->setRenderColour(1, 1, 1);
}
