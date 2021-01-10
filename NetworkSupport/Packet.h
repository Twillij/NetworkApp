#pragma once
#define MAX_DATA_SIZE 256
#include <iostream>

class Packet
{
public:
	Packet();
	template <class T>
	Packet(char a_dataType, T& a_data);
	~Packet() {}

	char dataType = '\0';	
	unsigned int senderID = 0;
	unsigned int objectID = 0;

	// Stores data from the passed reference
	template <class T>
	void StoreData(T& a_data);

	// Extracts data to the passed reference
	template <class T>
	void ExtractData(T& dataContainer);

	// Clears any stored data
	void ClearData();

private:
	char data[MAX_DATA_SIZE];
};

template<class T>
Packet::Packet(char a_dataType, T& a_data)
{
	dataType = a_dataType;
	StoreData(a_data);
}

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
