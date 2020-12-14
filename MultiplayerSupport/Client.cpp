#include "Client.h"

Client::Client()
{
	InitializeWinsock();

	// fill the block of memories 'hints' with zeroes
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // the address family is unspecified so that either IPv6 or IPv4 can be returned
	hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM is used to specify a stream socket
	hints.ai_protocol = IPPROTO_TCP; // IPPROTO_TCP is used to specify the TCP protocol
	hints.ai_flags = AI_PASSIVE; // AI_PASSIVE flag is used to bind function with the returned socket address structure in a call
}

Client::~Client()
{
	if (connectSocket != SOCKET_ERROR)
		closesocket(connectSocket);

	WSACleanup(); // used to terminate the use of ws2_32.dll
}

bool Client::InitializeWinsock()
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

	return true;
}

void Client::ConnectToServer()
{
	// resolve the server address and port
	int iResult = getaddrinfo(serverAddress, serverPort, &hints, &result);
	if (iResult != 0)
	{
		cout << "getaddrinfo failed: " << iResult << endl;
		exit(EXIT_FAILURE);
	}

	// attempt to connect to an address until one succeeds
	for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (connectSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		// Connect to server.
		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	// free the resources returned by getaddrinfo and print an error message
	freeaddrinfo(result);
	if (connectSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect to server!\n";
		exit(EXIT_FAILURE);
	}
}

void Client::ListenToServer()
{
	while (true)
	{
		Packet packet;
		ReceivePacket(packet);
	}
}

void Client::StartServerThread()
{
	if (connectSocket == INVALID_SOCKET)
	{
		cout << "Invalid connect socket. Has it been set up?" << endl;
		return;
	}

	thread server(&Client::ListenToServer, this);

	server.detach();
}

bool Client::SendPacket(Packet& packet)
{
	int iResult = send(connectSocket, (char*)&packet, sizeof(Packet), 0);
	if (iResult == SOCKET_ERROR)
	{
		cout << "Packet sending failed: " << WSAGetLastError() << endl;
		connectSocket = INVALID_SOCKET;
		exit(EXIT_FAILURE);
	}

	return true;
}

bool Client::ReceivePacket(Packet& packet)
{
	int iResult = recv(connectSocket, (char*)&packet, sizeof(Packet), 0);

	if (iResult > 0)
	{
		unprocessedPackets.push_back(packet);
		cout << "Packet received.\n";
		return true;
	}
	else if (iResult == 0)
	{
		cout << "Connection closed." << endl;
		connectSocket = INVALID_SOCKET;
		return false;
	}
	else
	{
		cout << "Packet receiving failed: " << WSAGetLastError() << endl;
		return false;
	}

	return false;
}
