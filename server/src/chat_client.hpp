#pragma once

#include "networking.hpp"
#include "dchat.hpp"
#include <vector>
#include <cinttypes>

namespace dchat {
    class server;
    class client
    {
      private:
        sockaddr_in          m_remote_address;
        SOCKET               m_socket;
        server* const        m_server;
        std::string          m_nick;
        // ...

      public:
        client(sockaddr_in const& remote_address, SOCKET s, server* server);
        ~client();
        bool update();
        bool send_message(std::string const& message);
        void disconnect();

        sockaddr_in        remote_address() const { return m_remote_address; }
        SOCKET             remote_socket() const { return m_socket; }
        std::string const& nick() const { return m_nick; }
        void               set_nick(std::string const& nick) { m_nick = nick; }
        bool                 HeaderDone;
        int                 Payload;

      protected:
        // void process_packet( /*...*/ );
    };
}