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
	renderer = new Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	font = new Font("../bin/font/consolas.ttf", 32);

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
	Input* input = Input::getInstance();

	if (input->isKeyDown(INPUT_KEY_SPACE))
	{
		int num = 420;
		Packet packet;
		packet.StoreData(num);
		client->SendPacket(packet);
	}

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
	
	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}