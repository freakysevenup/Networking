#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "Package.h"

class ServerTCP
{
public:
	ServerTCP(Uint16 port)
		:	m_port(port)
	{}
	~ServerTCP() 
	{
		SDL_GL_DeleteContext(m_context);
	}

	void run();

private:

	Package * m_serverPackage = new Package();
	Uint16 m_port;

	TCPsocket m_socketDescriptor = nullptr, m_clientSocketDescriptor = nullptr;
	IPaddress m_ipAddress, *m_remoteIPAddress;
	int m_quit, m_quit2;
	char m_buffer[BUFFER_SIZE];
	SDL_Window * m_window;
	SDL_GLContext m_context;

	glm::vec4 bgC = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


	bool init();
	bool resolve();
	bool open();
	bool close(TCPsocket socketToClose);
};

