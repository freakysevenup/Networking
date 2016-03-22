#define _CRT_SECURE_NO_WARNINGS

#include "ClientUDP.h"
#include <iostream>
#include <assert.h>


bool ClientUDP::init()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		std::cerr << "SDLNet_Init failed... " << SDLNet_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ClientUDP::open()
{
	/* Open a socket on random port */
	if (!(m_socketDescriptor = SDLNet_UDP_Open(0)))
	{
		std::cerr << "SDLNet_UDP_Open: %s\n" << SDLNet_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ClientUDP::resolveHost()
{
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&m_srvadd, m_host.c_str(), m_port) == -1)
	{
		std::cerr << "SDLNet_ResolveHost(%s %d): %s\n" << SDLNet_GetError() << std::endl;
		return false;
	}
	return true;
}

bool ClientUDP::allocatePacket()
{
	/* Allocate memory for the packet */
	if (!(m_packet = SDLNet_AllocPacket(BUFFER_SIZE)))
	{
		std::cerr << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError() << std::endl;
		return false;
	}
	return true;
}

void ClientUDP::run()
{
	//init();
	assert(init());

	//open();
	assert(open());

	//resolveHost();
	assert(resolveHost());

	//allocatePacket();
	assert(allocatePacket());

	//SDL_CreateWindow("Client Window", 0, 0, 100, 100, SDL_WINDOW_OPENGL);

	/* Main loop */
	m_quit = 0;
	while (!m_quit)
	{
		//while (SDL_PollEvent(&m_evt))
		//{
		//	m_clientPackage->e = m_evt;

		//	switch (m_clientPackage->e.type)
		//	{
		//	case SDL_KEYDOWN:
		//		printf("Key press detected\n");
		//		break;

		//	case SDL_KEYUP:
		//		printf("Key release detected\n");
		//		break;

		//	case SDL_MOUSEMOTION:
		//		printf("Mouse Moved\n");
		//		break;

		//	default:
		//		break;
		//	}
		//}

		//m_packet->len = (sizeof(Package));
		//m_packet->address.host = m_srvadd.host;	/* Set the destination host */
		//m_packet->address.port = m_srvadd.port;	/* And destination port */

		printf("Type Message: \n>");
		//scanf("%s", (char *)m_packet->data);

		std::getline(std::cin, m_input);

		m_packet->address.host = m_srvadd.host;	/* Set the destination host */
		m_packet->address.port = m_srvadd.port;	/* And destination port */

		m_packet->len = m_input.length() + 256;
		
		memcpy(m_packet->data, m_input.c_str(), m_packet->len);

		//memcpy(m_packet->data, m_clientPackage->data, sizeof(Package));

		if (!(SDLNet_UDP_Send(m_socketDescriptor, -1, m_packet) > 0))
		{
			printf("SDLNet_UDP_Send failed...\n");
		}
	}

	freePacket(*m_packet);
	SDLNet_Quit();
}

void ClientUDP::freePacket(UDPpacket & packetToFree)
{
	SDLNet_FreePacket(&packetToFree);
}