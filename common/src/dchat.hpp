#pragma once

#include <cinttypes>
#include <cstddef> // offsetof

namespace dchat {

    enum dchat_action
    {
        DCHAT_BROADCAST = 0,
        DCHAT_WHISPER = 1,
        DCHAT_CHANGE_NICKNAME = 2,
        DCHAT_LIST_CLIENTS = 3,
    };

#pragma pack(1)
    struct server_header
    {
        char Action;
        short Target;
        char Reserved;
        int PayloadSize;
    };
    static_assert(sizeof(server_header) == 8);

    struct client_header
    {
        int Length;
    };
    static_assert(sizeof(client_header) == 4);


}