#include "ServerUDP.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

void ServerUDP::run()
{
	initSystems();

	init();
	//assert(init());
	
	open();
	//assert(open());

	allocatePacket(BUFFER_SIZE);
	//assert(allocatePacket(BUFFER_SIZE));

	m_quit = 0;
	while (!m_quit)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(m_socketDescriptor, m_packet))
		{

			memcpy(m_serverPackage->data, m_packet->data, sizeof(Package));

			switch (m_serverPackage->e.type)
			{
			case SDL_QUIT:
				SDL_Quit();
				SDLNet_Quit();
				exit(0);
				break;
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				break;
			case SDL_KEYUP:
				printf("Key release detected\n");
				bgC = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

				if (m_serverPackage->e.button.button == SDLK_w)
				{
					rotateX += 0.2f;
					printf("%f\n", rotateX);
				}
				if (m_serverPackage->e.button.button == SDLK_s)
				{
					rotateX -= 0.2f;
				}
				if (m_serverPackage->e.button.button == SDLK_a)
				{
					rotateY += 0.2f;
				}
				if (m_serverPackage->e.button.button == SDLK_d)
				{
					rotateY -= 0.2f;
				}
				if (m_serverPackage->e.button.button == SDLK_q)
				{
					rotateZ += 0.2f;
				}
				if (m_serverPackage->e.button.button == SDLK_e)
				{
					rotateZ -= 0.2f;
				}
				break;
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
		}
		// update here

		m_view.Update();
		m_view.swapBuffer(0.0f, 0.0f, 0.0f, 1.0f);

		draw();
	}

	/* Clean and exit */
	freePacket(*m_packet);
	SDLNet_Quit();
}

void ServerUDP::initSystems()
{
	std::string title = "Window";
	ViewPort view(title, m_windowWidth, m_windowHeight, 0);
	setViewport(view);

	// Create Shape
	m_shape.createShape(SPHERE);
	Mesh shapeMesh(m_shape.getVertices(), m_shape.getVertices().size());

	m_shape.setPosition(glm::vec3(0.0f));
	m_shape.setScale(glm::vec3(1.0f));

	// Shader
	ShaderManager * shader = new ShaderManager();
	shader->init();
	shader->addShader(GL_VERTEX_SHADER, "./Assets/Shaders/basicShaderVert.glsl");
	shader->addShader(GL_FRAGMENT_SHADER, "./Assets/Shaders/basicShaderFrag.glsl");

	setShader(shader);

	// Setup Camera
	setCam(glm::vec3(0.0f, 1.0f, -4.0f), 60.0f, m_windowWidth / m_windowHeight, 1.0f, 100.0f);
}

void ServerUDP::draw()
{
	m_shader->enable();

	m_shape.setRotation(glm::vec3(rotateX, rotateY, rotateZ));

	GLint camUniform = m_shader->getUniformLocation("camera");
	glm::mat4 cameraMatrix = m_cam.matrix() * m_shape.getModel();
	glUniformMatrix4fv(camUniform, 1, GL_FALSE, &cameraMatrix[0][0]);
	GLint modelUniform = m_shader->getUniformLocation("model");
	glm::mat4 modelMatrix = m_shape.getModel();

	m_shape.draw();

	m_shader->disable();
}

bool ServerUDP::init()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("SDLNet initialized...\n");
	return true;
}

bool ServerUDP::open()
{
	/* Open a socket */
	if (!(m_socketDescriptor = SDLNet_UDP_Open(m_port)))
	{
		std::cerr << "SDLNet_UDP_Open: " << SDLNet_GetError() << std::endl;
		return false;
	}

	printf("Socket Opened...\n");
	return true;
}

bool ServerUDP::allocatePacket(int size)
{
	/* Make space for the packet */
	if (!(m_packet = SDLNet_AllocPacket(BUFFER_SIZE)))
	{
		std::cerr << "SDLNet_AllocPacket failed..\n" << std::endl;
		return false;
	}
	printf("Packet Allocated...\n");
	return true;
}

void ServerUDP::freePacket(UDPpacket & packetToClose)
{
	SDLNet_FreePacket(&packetToClose);
	m_shader->finalize();
}
