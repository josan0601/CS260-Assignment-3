#pragma once

#include "networking.hpp"
#include "dchat.hpp"
#include <cinttypes>
#include <vector>


// From client

namespace dchat {
    class client
    {
      private:
        SOCKET               m_socket{INVALID_SOCKET};
        std::vector<uint8_t> m_payload_buffer;
        bool                 m_quiet;
        // ...

      public:
        client();
        ~client();
        void start(char const* ip, uint16_t port, bool quiet);
        bool update();
        void close();

      protected:
        /*void process_packet(...)*/;
    };

}