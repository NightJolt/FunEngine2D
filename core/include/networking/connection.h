#pragma once

#include "../globals.h"
#include "../vec2.h"
#include "../pointer.h"

namespace fun::network {
    struct connection_info_t {
        connection_info_t();
        explicit connection_info_t(sf::TcpSocket*);
        connection_info_t(uint32_t, uint8_t, uint8_t);
        
        uint32_t ip;
        uint8_t remote_port;
        uint8_t local_port;
    };

    struct connection_t {
        explicit connection_t(sf::TcpSocket*);

        connection_info_t info;
        uptr_t <sf::TcpSocket> socket;
    };
}