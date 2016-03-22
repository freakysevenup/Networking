#pragma once
#include <string>
#include "Package.h"

class ClientUDP
{
public:
	ClientUDP(std::string host, Uint16 port)
		:	m_host(host),
			m_port(port)
	{
		// Empty
	}

	~ClientUDP()
	{
		// Empty
	}

	void run();

private:

	Uint16 m_port;
	std::string m_host;
	Package * m_clientPackage = new Package();
	UDPsocket m_socketDescriptor;
	IPaddress m_srvadd;
	UDPpacket *m_packet;
	int m_quit;
	SDL_Event m_evt;
	std::string m_input;

	bool init();
	bool open();
	bool resolveHost();
	bool allocatePacket();
	void freePacket(UDPpacket & packetToFree);

};

