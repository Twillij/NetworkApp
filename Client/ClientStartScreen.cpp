#include "ClientStartScreen.h"
#include <iostream>

ClientStartScreen::ClientStartScreen()
{
	serverAddrBox.position = { 640, 360 };
	serverAddrBox.extents = { 150, 20 };
}

void ClientStartScreen::Draw(Renderer2D* renderer, Font* font)
{
	if (!renderer || !font)
		return;

	renderer->drawBox(serverAddrBox.position.x, serverAddrBox.position.y, serverAddrBox.extents.x * 2, serverAddrBox.extents.y * 2);
	renderer->drawBox(serverPortBox.position.x, serverPortBox.position.y, serverPortBox.extents.x * 2, serverPortBox.extents.y * 2);
}
