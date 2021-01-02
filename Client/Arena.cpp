#include "Arena.h"
#include "Tank.h"

Arena::Arena()
{
}

void Arena::JoinServer(Server* server)
{
	if (server)
	{
		this->server = server;

	}
}
