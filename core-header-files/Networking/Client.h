#pragma once

#include "globals.h"

namespace fun {
    class Client {
    public:

        ~Client();

        bool Connect(const std::string&, unsigned short);

        void Update();

        void Send(const std::string&);

        std::string ReadNext();
        int UnreadCount();

    private:

        std::queue <sf::Packet> packets;

        sf::TcpSocket tcp_socket;
    };
}