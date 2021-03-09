#include "networking.hpp"
#include "chat_client.hpp"

#include <cstring>
#include <cinttypes>

void show_usage()
{
    std::cout << "usage: dchat_client [options]\n";
    std::cout << "Options:\n";
    std::cout << "\t--address <ipv4_address>       IPV4 interface in which to listen for incoming connections\n";
    std::cout << "\t--port <tcp_port>              port to open for the listening socket\n";
    std::cout << "\t--quiet                        Won't ask for cin messages, will only display remote ones\n";
    std::cout << "\t--help                         show this help\n";
}

int main(int argc, char const* argv[])
{
    char const* remote_ip   = "127.0.0.1";
    uint16_t    remote_port = 8001;
    bool        quiet       = false;

    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        char const* arg      = argv[i];
        char const* next_arg = nullptr;
        if (i + 1 < argc) next_arg = argv[i + 1];

        if (std::strcmp(arg, "--address") == 0 && next_arg)
        {
            i++;
            remote_ip = next_arg;
        }
        else if (std::strcmp(arg, "--port") == 0 && next_arg)
        {
            i++;
            remote_port = static_cast<uint16_t>(std::atoi(next_arg));
        }
        else if (std::strcmp(arg, "--quiet") == 0)
        {
            quiet = true;
        }
        else {
            show_usage();
        }
    }

    std::cout << "I'm the client \n";
    network_create();

    dchat::client c;
    c.start(remote_ip, remote_port, quiet);
    bool exit = false;
    while (!exit) {
        exit = !c.update();
    }

    system("pause");
    return 0;
}
