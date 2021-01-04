#include "ClientApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Arena.h"

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
	
	// world setup
	Arena* arena = new Arena();
	arena->JoinServer();
	worlds.push_back(arena);
	currentWorld = worlds[0];

	return true;
}

void ClientApp::shutdown()
{
	delete font;
	delete renderer;
	delete client;

	for (int i = 0; i < worlds.size(); ++i)
		delete worlds[i];
}

void ClientApp::update(float deltaTime)
{
	// input example
	Input* input = Input::getInstance();

	currentWorld->Update(deltaTime);

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
	currentWorld->Draw(renderer);

	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}