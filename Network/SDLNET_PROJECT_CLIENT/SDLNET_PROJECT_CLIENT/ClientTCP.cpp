#include "ClientTCP.h"
#include <assert.h>


bool ClientTCP::init()
{
	if (SDLNet_Init() < 0)
	{
		std::cerr << "SDLNet_Init " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("SDLNet initialized...\n");
	return true;

}

bool ClientTCP::resolveHost()
{
	if ((SDLNet_ResolveHost(&m_ipAddress, m_host.c_str(), m_port)) < 0)
	{
		std::cerr << "SDLNet_ResolveHost " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("Host Resolved\n");
	return true;
}

bool ClientTCP::open()
{
	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(m_socketDescriptor = SDLNet_TCP_Open(&m_ipAddress)))
	{
		std::cerr << "SDLNet_TCP_Open " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("Socket opened, connection to host made on port %i...\n", m_ipAddress.port);
	return true;
}

void ClientTCP::run()
{
	init();
	//assert(init());

	resolveHost();
	//assert(resolveHost());

	open();
	//assert(open());

	SDL_CreateWindow("Client Window", 0, 0, 400, 400, SDL_WINDOW_OPENGL);

	/* Send messages */
	m_quit = 0;
	while (!m_quit)
	{
		while (SDL_PollEvent(&evt))
		{
			m_clientPackage->e = evt;

			switch (m_clientPackage->e.type){
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				break;

			case SDL_KEYUP:
				printf("Key release detected\n");
				break;

			case SDL_MOUSEMOTION:
				printf("Mouse Moved\n");
				break;

			case SDL_MOUSEBUTTONDOWN:
				printf("Mouse Button Down\n");
				break;

			case SDL_MOUSEBUTTONUP:
				printf("Mouse Button Up\n");
				break;

			default:
				break;
			}
		}

		m_len = BUFFER_SIZE;
		if (SDLNet_TCP_Send(m_socketDescriptor, (void *)m_clientPackage->data, m_len) < m_len)
		{
			std::cerr << "SDLNet_TCP_Send " << SDLNet_GetError() << std::endl;
		}
	}

	closeSocket(m_socketDescriptor);
	SDLNet_Quit();
}

void ClientTCP::closeSocket(TCPsocket & socketToClose)
{
	SDLNet_TCP_Close(socketToClose);
}