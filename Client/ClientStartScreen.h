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
		vec2 pos = { 0, 0 };
		vec2 extents = { 1, 1 };
		char text[40] = "";
	};

	TextBox serverAddrBox;
	TextBox serverPortBox;

	TextBox* currentTextBox = nullptr;

	virtual void Update(float deltaTime) override;
	virtual void Draw(Renderer2D* renderer, Font* font) override;
};
