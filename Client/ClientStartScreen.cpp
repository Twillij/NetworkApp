#include "ClientStartScreen.h"

void ClientStartScreen::Draw(Renderer2D* renderer, Font* font)
{
	if (!renderer || !font)
		return;

	renderer->drawBox(0, 0, 0, 0);
}
