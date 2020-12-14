#pragma once
#include "Packet.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <vector>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

using std::cout;
using std::endl;
using std::vector;
using std::thread;

class Server
{
public:
	Server();
	~Server();

	const char* port = "27015";

	fd_set clients;
	SOCKET listenSocket = INVALID_SOCKET;
	unsigned int maxClients = INT_MAX;

	vector<Packet> unprocessedPackets;

	///<summary>Initializes winsock.
	///Returns true if initialization succeeds, or false otherwise.</summary>
	static bool InitializeWinsock();

	void SetupListenSocket();
	void ListenToClients();
	void StartListeningThread();
	void HandleNewClient(SOCKET newClient);

	bool SendPacket(SOCKET& recipient, Packet& packet);
	bool ReceivePacket(SOCKET& sender, Packet& packet);

private:
	addrinfo* result = NULL;
	addrinfo hints;
};