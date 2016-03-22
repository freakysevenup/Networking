#include "ServerTCP.h"
#include <iostream>
#include <string>
#include <assert.h>

bool ServerTCP::init()
{
	if (SDLNet_Init() < 0)
	{
		std::cerr << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("SDLNet initialized...\n");
	return true;
}

bool ServerTCP::resolve()
{
	if (SDLNet_ResolveHost(&m_ipAddress, NULL, m_port))
	{
		std::cerr << "SDLNet_ResolveHost : " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("Resolved Host...\n");
	return true;
}

bool ServerTCP::open()
{
	if (!(m_socketDescriptor = SDLNet_TCP_Open(&m_ipAddress)))
	{
		std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("Socket Opened...\n");
	return true;
}

void ServerTCP::run()
{
	//init();
	assert(init());

	//resolve();
	assert(resolve());

	//open();
	assert(open());

	m_window = SDL_CreateWindow("Server Window", 600, 0, 100, 100, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);
	glewInit();

	m_quit = 0;
	while (!m_quit)
	{
		//printf("...\n");
		/* This check the sd if there is a pending connection.
		* If there is one, accept that, and open a new socket for communicating */
		if ((m_clientSocketDescriptor = SDLNet_TCP_Accept(m_socketDescriptor)))
		{
			/* Now we can communicate with the client using csd socket
			* sd will remain opened waiting other connections */

			/* Get the remote address */
			if ((m_remoteIPAddress = SDLNet_TCP_GetPeerAddress(m_clientSocketDescriptor)))
				/* Print the address, converting in the host format */
				printf("Host connected: %x %d\n", SDLNet_Read32(&m_remoteIPAddress->host), SDLNet_Read16(&m_remoteIPAddress->port));
			else
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());

			m_quit2 = 0;
			while (!m_quit2)
			{
				if (SDLNet_TCP_Recv(m_clientSocketDescriptor, m_buffer, sizeof(m_buffer)) > 0)
				{
					//for (int i = 0; i < sizeof(serverPackage->data); i++)
					//{
					//	serverPacakge->data[i] = m_buffer[i];
					//}

					memcpy(m_serverPackage->data, m_buffer, sizeof(Package));

					if (strcmp(m_buffer, "exit") == 0)	/* Terminate this connection */
					{
						m_quit2 = 1;
						printf("Terminate connection\n");
					}
					if (strcmp(m_buffer, "quit") == 0)	/* Quit the program */
					{
						m_quit2 = 1;
						m_quit = 1;
						printf("Quit program\n");
					}
				}

				switch (m_serverPackage->e.type){
				case SDL_KEYDOWN:
					printf("Key press detected\n");
					bgC = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					break;

				case SDL_KEYUP:
					printf("Key release detected\n");
					bgC = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
					break;

				case SDL_MOUSEMOTION:
					printf("Mouse Moved\n");
					bgC = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
					break;

				case SDL_MOUSEBUTTONDOWN:
					printf("Mouse Button Down\n");
					bgC = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
					break;

				case SDL_MOUSEBUTTONUP:
					printf("Mouse Button Up\n");
					bgC = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
					break;

				default:
					break;
				}

				SDL_GL_SwapWindow(m_window);
				glClearColor(bgC.x, bgC.y, bgC.z, bgC.a);
				glClear(GL_COLOR_BUFFER_BIT);
			}

			/* Close the client socket */
			//close(m_clientSocketDescriptor);
			assert(close(m_clientSocketDescriptor));
		}
	}

	//close(m_socketDescriptor);
	assert(close(m_socketDescriptor));

	SDLNet_Quit();
}

bool ServerTCP::close(TCPsocket socketToClose)
{
	SDLNet_TCP_Close(socketToClose);
	if (!socketToClose == NULL)
	{
		return false;
	}
	return true;
}
