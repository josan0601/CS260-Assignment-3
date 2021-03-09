#include "networking.hpp"
#include "chat_server.hpp"
#include "dchat.hpp"

#include <iostream>
#include <cstring>
#include <sstream>

void show_usage()
{
    std::cout << "usage: dchat_server.exe [options]\n";
    std::cout << "Options:\n";
    std::cout << "\t--address <ipv4_address>       IPV4 interface in which to listen for incoming connections\n";
    std::cout << "\t--port <tcp_port>              port to open for the listening socket\n";
    std::cout << "\t--help                         show this help\n";
}

int main(int argc, char const* argv[])
{
    char const* local_ip   = "0.0.0.0";
    uint16_t    local_port = 8001;

    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        char const* arg      = argv[i];
        char const* next_arg = nullptr;
        if (i + 1 < argc) next_arg = argv[i + 1];

        if (std::strcmp(arg, "--address") == 0 && next_arg)
        {
            i++;
            local_ip = next_arg;
        }
        else if (std::strcmp(arg, "--port") == 0 && next_arg)
        {
            i++;
            local_port = static_cast<uint16_t>(std::atoi(next_arg));
        }
        else {
            show_usage();
            return 0;
        }
    }

    std::cout << "I'm the server\n";
     //
    network_create();
    dchat::server s;
    bool Started = s.start(local_ip, local_port);

    if (!Started)
    {
        std::cout << "Something went wrong \n";
        return 0;
    }
    int Size = sizeof(dchat::server_header);
    Size;
    //std::cout << "Size of server header is :" << sizeof(dchat::server_header) << std::endl;
    //std::cout << "Size of client header is :" << sizeof(dchat::client_header) << std::endl;

    bool exit = false;
    while (!exit) {
        exit = !s.update();
    }
    network_destroy();
    system("pause");
    return 0;
}