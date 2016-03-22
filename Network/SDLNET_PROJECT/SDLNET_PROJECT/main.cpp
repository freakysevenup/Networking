//#include "ServerTCP.h"
#include "ServerUDP.h"

int main(int argc, char** argv)
{
	//ServerTCP server(0xEC79);
	//server.run();

	ServerUDP server(0xEC79);
	server.run();

	return 0;
}