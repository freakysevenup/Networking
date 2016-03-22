//#include "ClientTCP.h"
#include "ClientUDP.h"

int main(int argc, char** argv)
{
	//ClientTCP client("localhost", 0xEC79);
	//client.run();

	//ClientUDP client("localhost", 0xEC79);
	ClientUDP client("munro.humber.ca", 40048);
	client.run();

	// http://www.cplusplus.com/forum/unices/116977/

	return 0;
}