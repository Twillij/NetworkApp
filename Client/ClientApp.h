#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Client.h"
#include "World.h"

using namespace aie;

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
	vector<World*> worlds;
	World* currentWorld = nullptr;
};
