#pragma once
#include "Packet.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <vector>
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

	vector<Packet> unprocessedPackets;

	///<summary>Initializes winsock.
	///Returns true if initialization succeeds, or false otherwise.</summary>
	static bool InitializeWinsock();

	void ConnectToServer();
	void ListenToServer();
	void StartServerThread();

	bool SendPacket(Packet& packet);
	bool ReceivePacket(Packet& packet);

private:
	addrinfo* result = NULL;
	addrinfo hints;
};