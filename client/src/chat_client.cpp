//#include "..\..\server\src\chat_client.hpp"
//#include "..\..\server\src\chat_client.hpp"
//#include "..\..\server\src\chat_client.hpp"
//#include "..\..\server\src\chat_client.hpp"
#include "chat_client.hpp"
#include "networking.hpp"
#include "dchat.hpp"

#include <cstring>
#include <cassert>

namespace dchat {
	// From Client

    client::client()
    {
        m_quiet = false;
    }

    client::~client()
    {

    }

    bool client::update()
    {
        if (!m_quiet) {
            server_header NewHeader;

            
            std::string message;
            std::string Data;
            std::getline(std::cin, message);
            char command = '\\';

            if (message[0] == command)
            {
                if (message.find("whisper") != std::string::npos)
                {
                    NewHeader.Action = 1;
                    short mTarget = static_cast<short>(std::atoi(&message[9]));
                    NewHeader.Target = mTarget;
                    NewHeader.PayloadSize = static_cast<int>(message.size()) - (10 + static_cast<int>(log10(mTarget)) + 1);
                    Data = message.substr((10 + static_cast<int>(log10(mTarget)) + 1), NewHeader.PayloadSize);
                }
                else if (message.find("nick"))
                {
                    NewHeader.Action = 2;
                    NewHeader.Target = 0;
                    NewHeader.PayloadSize = static_cast<int>(message.size()) - 6;
                    Data = message.substr(6, NewHeader.PayloadSize);

                }
                else if (message.find("list"))
                {
                    NewHeader.Action = 3;
                    NewHeader.Target = 0;
                    NewHeader.PayloadSize = 0;
                }
                else // No correct command was given
                {
                    return false;
                }
            }
            else
            {
                NewHeader.Action = 0;
                NewHeader.Target = 0;
                NewHeader.PayloadSize = static_cast<int>(message.size());
                Data = message;
            }

            // Send Header
            send(m_socket, reinterpret_cast<char*>(&NewHeader), sizeof(NewHeader), 0);

            // Send Data
            if(NewHeader.Action != 3)
                send(m_socket, Data.c_str(), static_cast<int>(Data.size()), 0);
            
            std::cout << "Message sent is : " << Data << std::endl;
            std::cout << "Length of message is : " << Data.size() << std::endl;
        }

        // Check if any messages arrived

        return true;
    }

    void client::start(char const* ip, uint16_t port, bool quiet)
    {
        // Create socket
        SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        assert(s != INVALID_SOCKET);


        // Remote endpoint
        sockaddr_in remote_endpoint{};

        // Convert IP from string to network address
        auto err = inet_pton(AF_INET, ip, &remote_endpoint.sin_addr);
        assert(err == 1);

        // Set the port
        remote_endpoint.sin_port = htons(port);
        remote_endpoint.sin_family = AF_INET;

        err = connect(s, reinterpret_cast<sockaddr*>(&remote_endpoint), sizeof(remote_endpoint));
        if (err == SOCKET_ERROR)
        {
            auto err_code = WSAGetLastError();
            if (err_code != WSAEWOULDBLOCK)
                std::cerr << err_code << std::endl;
        }

        m_quiet = quiet;
        m_socket = s;
    }

    void client::close()
    {

    }
}