#pragma once
#include <string>
#include <iostream>
#include "Package.h"

class ClientTCP
{
public:
	ClientTCP(std::string host, Uint16 port)
		:	m_host(host),
			m_port(port)
	{
		// Empty
	}

	~ClientTCP()
	{
		// Empty
	}

	void run();

private:
	Package * m_clientPackage = new Package();
	std::string m_host;
	Uint16 m_port;
	IPaddress m_ipAddress;				/* Server address */
	TCPsocket m_socketDescriptor;		/* Socket descriptor */
	int m_quit, m_len;
	char buffer[BUFFER_SIZE];
	std::string input;

	SDL_Event evt;

	bool init();
	bool resolveHost();
	bool open();
	void closeSocket(TCPsocket & socketToClose);
};

