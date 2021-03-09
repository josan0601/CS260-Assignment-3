#include "chat_server.hpp"
#include "chat_client.hpp"
#include <cassert>

dchat::server::server()
{
}

dchat::server::~server()
{
}

bool dchat::server::start(char const* ip, uint16_t port)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(s != INVALID_SOCKET);
	
	m_socket = s;

	sockaddr_in local_endpoint{};
	local_endpoint.sin_family = AF_INET;
	local_endpoint.sin_port = htons(port);
	auto err = inet_pton(AF_INET, ip, &local_endpoint.sin_addr);
	if (err != 1)
		return false;

	// Bind socket
	err = bind(s, reinterpret_cast<sockaddr*>(&local_endpoint), sizeof(local_endpoint));
	if (err == SOCKET_ERROR)
		return false;

	err = listen(s, SOMAXCONN);
	if (err == SOCKET_ERROR)
		return false;

	set_socket_blocking(s, false);


	return true;
}

bool dchat::server::update()
{
	sockaddr_in remote_endpoint{};
	int remote_endpoint_size = sizeof(remote_endpoint);
	SOCKET remote_socket = accept(m_socket, reinterpret_cast<sockaddr*>(&remote_endpoint), &remote_endpoint_size);
	
	if (remote_socket == INVALID_SOCKET)
	{
		auto ErrCode = WSAGetLastError();
		if (ErrCode == WSAEWOULDBLOCK)
		{	// No users were added this iteration
		}
		else
		{
			std::cout << "Something went wrong accepting a client: " << ErrCode << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "I accepted a new client " << std::endl;
		set_socket_blocking(remote_socket, false);
		dchat::client* NewClient = new client(remote_endpoint, remote_socket, this);
		m_clients[remote_socket] = NewClient;

		// Create poll for client and add it
		WSAPOLLFD NewPoll;
		NewPoll.fd = remote_socket;
		NewPoll.events = POLLIN;
		NewPoll.revents = 0;
		m_active_sockets.push_back(NewPoll);

	}

	if (m_active_sockets.size() >= 1)
	{
		auto PollRes = WSAPoll(&(m_active_sockets[0]), static_cast<ULONG>(m_active_sockets.size()), 16);

		if (PollRes == SOCKET_ERROR)
		{

		}
		if (PollRes == 0)
		{
			return true;
		}
		else
		{
			for (unsigned i = 0; i < m_active_sockets.size(); i++)
			{
				if (m_active_sockets[i].revents == 0)
					continue;

				m_active_sockets[i].revents = 0;

				SOCKET CurrentSock = m_active_sockets[i].fd;

				if (m_clients[CurrentSock]->HeaderDone)	// Parse only message
				{
					char* recv_buffer;
					recv_buffer = new char[m_clients[CurrentSock]->Payload];
					auto rcv = recv(CurrentSock, recv_buffer, sizeof(recv_buffer), MSG_PEEK);
					if (rcv != m_clients[CurrentSock]->Payload)
					{
						recv_buffer[rcv] = 0;
						std::cout << recv_buffer << std::endl;
					}
				}
				else         // Parse header
				{
					char* recv_buffer;
					recv_buffer = new char[sizeof(server_header)];
					auto rcv = recv(CurrentSock, recv_buffer, sizeof(recv_buffer), MSG_PEEK);	// Peek for header

					if (rcv != sizeof(recv_buffer)) // Header is not complete
						continue;

					rcv = recv(CurrentSock, recv_buffer, sizeof(recv_buffer), 0);	// Receive actual header
					server_header* NewHeader = reinterpret_cast<server_header*>(recv_buffer);

					m_clients[CurrentSock]->HeaderDone = true;
					m_clients[CurrentSock]->Payload = NewHeader->PayloadSize;



				}
			}
		}

	}

	return true;
}
