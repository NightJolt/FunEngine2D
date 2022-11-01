#pragma once

#include "../globals.h"
#include "packet_storage.h"

namespace fun::network {
    class client_t {
    public:

        client_t();
        ~client_t();

        bool connect(const std::string&, unsigned short);
        void disconnect();

        void send(const std::string&);
        void receive();

        packet_storage_t& get_packets();

        bool check_connection();

    private:

        sf::TcpSocket server;

        packet_storage_t packet_storage;

        bool is_connected;
    };
}
