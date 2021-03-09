#include "networking.hpp"
#include <iostream>
#include <cstring>
#include <cassert>
#include <signal.h>

#ifdef WIN32
void network_create()
{
	WSADATA data{};
	auto err = WSAStartup(MAKEWORD(2, 2), &data);
	
	if (err != 0 || LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion != 2))
	{
		std::cout << "Something went wrong initializing \n";
		abort();
	}
}

void network_destroy()
{
	WSACleanup();
}

/**
 * @brief 
 *  Sets whether a socket would be blocking or not
 * @param fd 
 * @param blocking 
 */
void set_socket_blocking(SOCKET fd, bool blocking)
{
	u_long iMode = 1;
	blocking ? iMode = 0 : iMode = 1;

	auto err = ioctlsocket(fd, FIONBIO, &iMode);
	assert(err == 0);
}

#else

#endif
