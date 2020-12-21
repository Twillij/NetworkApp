#include "Packet.h"

Packet::Packet()
{
	ClearData();
}

void Packet::ClearData()
{
	dataType = '\0';

	for (int i = 0; i < MAX_DATA_SIZE; ++i)
		data[i] = '\0';
}