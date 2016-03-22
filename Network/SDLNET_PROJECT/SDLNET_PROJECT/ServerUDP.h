#pragma once
#include "Package.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "Camera3D.h"
#include "Shape.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "Viewport.h"

class ServerUDP
{
public:
	ServerUDP(Uint16 port)
		: m_port(port)
	{}

	~ServerUDP() { }

	void run();

private:
	Uint16 m_port;

	UDPsocket m_socketDescriptor;       /* Socket descriptor */
	UDPpacket *m_packet;       /* Pointer to packet memory */
	int m_quit;
	Package *m_serverPackage = new Package();

	glm::vec4 bgC = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	bool init();
	bool allocatePacket(int size);
	bool open();
	void freePacket(UDPpacket & packetToFree);
	void initSystems();
	void draw();

	void setViewport(ViewPort & view) { m_view = view; }
	void setShader(ShaderManager * shader) { m_shader = shader; }
	void setCam(glm::vec3 position, float viewAngle, float aspectRatio, float near, float far) 
	{
		m_cam.setFieldOfView(viewAngle);
		m_cam.setPosition(position);
		m_cam.setViewportAspectRatio(aspectRatio);
		m_cam.setNearAndFarPlanes(near, far);
	}

	// Graphical Variables
	Shape m_shape;
	Camera3D m_cam;
	ShaderManager * m_shader;
	ViewPort m_view;
	int m_windowWidth = 400, m_windowHeight = 400;
	float rotateX = 0, rotateY = 0, rotateZ = 0;
};

