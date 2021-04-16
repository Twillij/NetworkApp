#pragma once
#include "World.h"
#include <glm/vec2.hpp>

using glm::vec2;

class ClientStartScreen : public World
{
public:
	ClientStartScreen();
	~ClientStartScreen() {}

	struct TextBox
	{
		vec2 position;
		vec2 extents;
		const char* text;
	};

	TextBox serverAddrBox;
	TextBox serverPortBox;

	virtual void Draw(Renderer2D* renderer, Font* font) override;
};
