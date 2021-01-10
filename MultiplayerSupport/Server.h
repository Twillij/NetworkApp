#pragma once
#include "Packet.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <deque>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Server
{
public:
	Server();
	~Server();

	const char* port = "27015";

	fd_set clients;
	SOCKET listenSocket = INVALID_SOCKET;
	unsigned int maxClients = INT_MAX;

	deque<Packet> unprocessedPackets;

	// Initializes winsock. Returns true if initialization succeeds, or false otherwise.
	static bool InitializeWinsock();

	// Sets up a listening socket for clients
	void SetupListenSocket();

	// Uses the listening socket to listen to clients on a loop
	void ListenToClients();

	// Starts a thread for listening to clients
	void StartListeningThread();

	// Handles the passed socket as a new client connection
	void HandleNewClient(SOCKET newClient);

	// Returns a socket with a matching ID from the socket list, or an invalid socket otherwise
	SOCKET GetSocket(unsigned int socketID);

	// Sends a packet through the given socket
	bool SendPacket(SOCKET& recipient, Packet& packet);

	// Receives a packet through the given socket
	bool ReceivePacket(SOCKET& sender, Packet& packet);

private:
	addrinfo* result = NULL;
	addrinfo hints;
};