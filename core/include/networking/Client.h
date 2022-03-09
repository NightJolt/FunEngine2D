#pragma once

#include "../Globals.h"

namespace fun {
    class Client {
    public:

        ~Client();

        bool Connect(const std::string&, unsigned short);
        void Disconnect();

        void RecieveData();

        void Send(const std::string&);

        std::string ReadNext();
        int PacketsLeft();

    private:

        std::queue <sf::Packet> packets;

        sf::TcpSocket tcp_socket;
    };
}