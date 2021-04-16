#include "ClientApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Arena.h"
#include "ClientStartScreen.h"

ClientApp::ClientApp()
{
}

ClientApp::~ClientApp()
{
}

bool ClientApp::startup()
{
	renderer = new Renderer2D();
	font = new Font("./font/consolas.ttf", 32);

	// arena setup
	Arena* arena = new Arena();
	worlds.push_back(arena);

	// start screen setup
	ClientStartScreen* startScreen = new ClientStartScreen();
	startScreen->currentWorld = &currentWorld;
	startScreen->nextWorld = arena;
	worlds.push_back(startScreen);

	// set the initial world as the start screen
	currentWorld = startScreen;

	return true;
}

void ClientApp::shutdown()
{
	delete font;
	delete renderer;

	for (int i = 0; i < worlds.size(); ++i)
		delete worlds[i];
}

void ClientApp::update(float deltaTime)
{
	Input* input = Input::getInstance();

	// update the current world
	currentWorld->Update(deltaTime);
	
	// exit the application
	if (input->isKeyDown(INPUT_KEY_ESCAPE))
		quit();
}

void ClientApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	renderer->begin();

	// draw your stuff here!
	currentWorld->Draw(renderer, font);

	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}