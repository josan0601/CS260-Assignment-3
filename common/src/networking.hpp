#include <iostream>
#include <string>

#ifdef __linux__
#include <sys/socket.h> // sockets
#include <sys/poll.h>   // poll
#include <netinet/in.h> // sockaddr_in
#include <netdb.h>      // addrinfo
#include <arpa/inet.h>  // inet_pton
#include <errno.h>      // Errors
#include <unistd.h>     // close()
#include <fcntl.h>      // Non-Blocking sockets
// Porting from windows code
#define WSAGetLastError() errno                        // In windows, errors are stored in WSAGetLastError, most errors are similar
#define WSAPoll(fds, c, timeout) poll(fds, c, timeout) // In windows, there is native poll. ALMOST similar.
#define WSAPOLLFD pollfd                               //
#define SOCKET int                                     // In windows, SOCKET is the socket data type, not file descriptors
#define INVALID_SOCKET ~0                              //
#define SOCKET_ERROR -1                                //
#define closesocket(fd) close(fd)                      // In windows, close is closesocket (they are not file descriptors in windows)
#define WSAEWOULDBLOCK EWOULDBLOCK
#elif _WIN32
#include <WinSock2.h> // Basic WSA features (socket, connect, ...)
#include <WS2tcpip.h> // More WSA features (such inet_pton, inet_ntop, ...)
using socklen_t = int; // Trick for accept
#endif

void network_create();
void network_destroy();

/**
 * @brief 
 *  Sets whether a socket would be blocking or not
 * @param fd 
 * @param blocking 
 */
void set_socket_blocking(SOCKET fd, bool blocking);

/**
 * @brief 
 *  Reads an string in format {ip}[:port] into an address
 * @param is 
 * @param addr 
 * @return std::istream& 
 */
std::istream& operator>>(std::istream& is, sockaddr_in& addr);
std::istream& operator>>(std::istream& is, in_addr& ipv4);

/**
 * @brief 
 *  Writes an address with the format {ip}[:port]. Port is not written if 0
 * @param src 
 * @return sockaddr_in 
 */
std::ostream& operator<<(std::ostream& os, sockaddr_in const& addr);
std::ostream& operator<<(std::ostream& os, in_addr const& ipv4);

/**
 * @brief 
 *  Converts a c-string into an ip address. Throws if fails.
 * @param str 
 * @return in_addr 
 */
in_addr cstr_to_ipv4(char const* str);

/**
 * @brief 
 *  Converts an address to an std::string
 * @param addr 
 * @return std::string 
 */
std::string ipv4_to_str(in_addr const& addr);

/**
 * @brief 
 *  Ensures that all the data has been sent, or fails
 * @param s 
 * @param data 
 * @param count 
 * @return true 
 * @return false 
 */
bool send_entirely(SOCKET s, void const* data, uint32_t count);
