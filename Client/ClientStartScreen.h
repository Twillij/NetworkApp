#pragma once
#include "World.h"
class ClientStartScreen : public World
{
public:
	ClientStartScreen() {}
	~ClientStartScreen() {}

	virtual void Draw(Renderer2D* renderer, Font* font) override;
};
