#pragma once

#include "../globals.h"

namespace fun {
    class client_t {
    public:

        ~client_t();

        bool connect(const std::string&, unsigned short);
        void disconnect();

        void receive_data();

        void send(const std::string&);

        std::string read_next();
        int packets_left();

    private:

        std::queue <sf::Packet> packets;

        sf::TcpSocket tcp_socket;
    };
}
