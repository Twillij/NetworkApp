#pragma once
#define MAX_PACKET_SIZE 512
#include <iostream>

class Packet
{
public:
	Packet();
	template <class T>
	Packet(T& a_data) { StoreData(a_data); }
	~Packet() {}

	char dataType = '\0';
	int senderID = -1;

	template <class T>
	void StoreData(T& a_data);

	template <class T>
	void ExtractData(T& dataContainer);

	void ClearData();

private:
	char data[MAX_PACKET_SIZE];
};

template<class T>
void Packet::StoreData(T& a_data)
{
	char* buf = (char*)&a_data;
	int len = sizeof(T);

	memcpy(data, buf, len);
}

template<class T>
void Packet::ExtractData(T& dataContainer)
{
	memcpy(&dataContainer, data, sizeof(T));
}
