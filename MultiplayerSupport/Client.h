#pragma once
#include "Packet.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <deque>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Client
{
public:
	Client();
	~Client();

	const char* serverAddress = "localhost";
	const char* serverPort = "27015";

	SOCKET connectSocket = INVALID_SOCKET;
	deque<Packet> unprocessedPackets;

	/// Initializes winsock. Returns true if initialization succeeds, or false otherwise.
	static bool InitializeWinsock();

	// Attempts to connect to the given server address and port
	void ConnectToServer();

	// Uses the connect socket to listen to the server on a loop
	void ListenToServer();

	// Starts a thread for listening to the server
	void StartServerThread();

	// Sends a packet to the server
	bool SendPacket(Packet& packet);

	// Receives a packet from the server
	bool ReceivePacket();

private:
	addrinfo* result = NULL;
	addrinfo hints;
};