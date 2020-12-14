#include "ClientApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

ClientApp::ClientApp()
{
}

ClientApp::~ClientApp()
{
}

bool ClientApp::startup()
{
	renderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	font = new aie::Font("../bin/font/consolas.ttf", 32);

	client = new Client();

	// connect client to server
	client->ConnectToServer();

	// start listening to the server on a different thread
	client->StartServerThread();

	return true;
}

void ClientApp::shutdown()
{
	delete font;
	delete renderer;
	delete client;
}

void ClientApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ClientApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	renderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}