#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Client.h"

using aie::Font;
using aie::Renderer2D;

class ClientApp : public aie::Application
{
public:

	ClientApp();
	virtual ~ClientApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	Renderer2D*	renderer;
	Font* font;
	Client* client;
};