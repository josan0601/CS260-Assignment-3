#pragma once

#include "networking.hpp"
#include <cinttypes>
#include <vector>
#include <unordered_map>

namespace dchat {
    class client;
    class server
    {
      private:
        SOCKET                              m_socket{INVALID_SOCKET};
        std::vector<WSAPOLLFD>              m_active_sockets;
        std::unordered_map<SOCKET, client*> m_clients;

      public:
        server();
        ~server();
        bool start(char const* ip, uint16_t port);
        bool update();
        void send_broadcast(client const* src, char const* msg);
        void send_whisper(client const* src, unsigned dst_id, std::string const& msg);
        void send_user_list(client* dst);

      protected:
    };
}