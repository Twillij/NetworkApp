#include "Server.h"
#include <string>

Server::Server()
{
	InitializeWinsock();

	// fill the block of memories 'hints' with zeroes
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // AF_INET is used to specify the IPv4 address family
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM is used to specify a stream socket
	hints.ai_protocol = IPPROTO_TCP; // IPPROTO_TCP is used to specify the TCP protocol
	hints.ai_flags = AI_PASSIVE; // AI_PASSIVE flag is used to bind function with the returned socket address structure in a call

	// resolve the local address and port to be used by the server
	int iResult = getaddrinfo(NULL, port, &hints, &result);
	if (iResult != 0)
	{
		cout << "getaddrinfo failed: " << iResult << endl;
		exit(EXIT_FAILURE);
	}

	// fill the clients list with zeroes
	FD_ZERO(&clients);
}

Server::~Server()
{
	for (int i = 0; i < clients.fd_count; ++i)
		closesocket(clients.fd_array[i]);

	WSACleanup(); // used to terminate the use of ws2_32.dll
}

bool Server::InitializeWinsock()
{
	WSADATA wsaData;

	// wsastartup is called to initialize use of ws2_32.dll
	// wsastartup requests version 2.2 of winsock on the system,
	// then sets it as the highest version of winsock support the caller can use
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{
		cout << "WSA Startup failed: " << iResult << endl;
		return false;
	}

	cout << "WSA libraries initialized." << endl;

	return true;
}

void Server::SetupListenSocket()
{
	// create a SOCKET for the server to listen for client connections
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		exit(EXIT_FAILURE);
	}

	// Setup the TCP listening socket
	int iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Bind failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		listenSocket = INVALID_SOCKET;
		exit(EXIT_FAILURE);
	}
	// address info returned by addrinfo 'result' is no longer needed
	// free the memory allocated by getaddrinfo for this address info
	freeaddrinfo(result);

	// place the socket in a state in which it is listening for an incoming connection
	// SOMAXCONN is a special constant instructs the winsock to allow a max reasonable number of pending connections in queue
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "Listen failed with error: " << WSAGetLastError() << endl;
		listenSocket = INVALID_SOCKET;
		exit(EXIT_FAILURE);
	}

	// add the listen socket to the master fd set
	FD_SET(listenSocket, &clients);
}

void Server::ListenToClients()
{
	while (clients.fd_count < maxClients)
	{
		// create a temp client socket list for filtering
		fd_set temp = clients;
		// filter the temp list to only those that have pending connection
		int iResult = select(0, &temp, nullptr, nullptr, nullptr);
		if (iResult == SOCKET_ERROR)
		{
			cout << "Unable to check for pending connections: " << WSAGetLastError() << endl;
			return;
		}

		// for each pending connection, check if they are a new or existing client
		for (int i = 0; i < iResult; i++)
		{
			SOCKET current = temp.fd_array[i];

			// if there is a pending connection from the listen socket, it is a new client
			if (current == listenSocket)
			{
				HandleNewClient(current);
			}
			else // otherwise it is an existing client
			{

				cout << "Pending packet from an existing client." << endl;
				Packet newPacket;
				ReceivePacket(current, newPacket);
				newPacket.senderID = current;
			}
		}
	}
}

void Server::StartListeningThread()
{
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "Invalid listen socket. Has it been set up?" << endl;
		return;
	}

	thread listen(&Server::ListenToClients, this);

	listen.detach();
}

void Server::HandleNewClient(SOCKET newClient)
{
	SOCKET client = accept(newClient, nullptr, nullptr);
	if (client == INVALID_SOCKET)
	{
		cout << "Failed to accept new connection: " << WSAGetLastError() << endl;
		return;
	}

	FD_SET(client, &clients);
	cout << "New client connection established." << endl;
}

SOCKET Server::GetSocket(unsigned int socketID)
{
	for (int i = 0; i < clients.fd_count; ++i)
	{
		if (clients.fd_array[i] == socketID)
		{
			return clients.fd_array[i];
		}
	}

	return INVALID_SOCKET;
}

bool Server::SendPacket(SOCKET& recipient, Packet& packet)
{
	int iResult = send(recipient, (char*)&packet, sizeof(Packet), 0);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Packet sending failed: " << WSAGetLastError() << endl;
		listenSocket = INVALID_SOCKET;
		exit(EXIT_FAILURE);
	}

	return true;
}

bool Server::ReceivePacket(SOCKET& sender, Packet& packet)
{
	int iResult = recv(sender, (char*)&packet, sizeof(Packet), 0);
	if (iResult > 0)
	{
		packet.senderID = (int)sender;
		unprocessedPackets.push_back(packet);
		cout << "Packet received." << endl;
		return true;
	}
	else if (iResult == 0)
	{
		cout << "Connection closed.\n";
		closesocket(sender);
		FD_CLR(sender, &clients);
		return false;
	}
	else
	{
		cout << "Packet receiving failed: %d\n", WSAGetLastError();
		return false;
	}

	return false;
}
