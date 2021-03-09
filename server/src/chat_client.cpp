//#include "..\..\client\src\chat_client.hpp"
#include "chat_client.hpp"

namespace dchat
{

    client::client(sockaddr_in const& remote_address, SOCKET s, server* server) : m_server(server), m_socket(s), m_remote_address(remote_address)
    {
        HeaderDone = false;
    }


    client::~client()
    {
    }

    bool client::update()
    {

        return false;
    }

    bool client::send_message(std::string const& message)
    {
        message;
        return false;
    }

    void client::disconnect()
    {
    }
}