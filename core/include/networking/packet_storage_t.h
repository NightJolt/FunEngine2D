#pragma once

#include "../globals.h"

namespace fun {
    class packet_storage_t {
    public:

        struct packet_t {
            std::string data;
            sf::TcpSocket* sender;
        };

        void enqueue(const sf::Packet&, sf::TcpSocket*);
        packet_t read();
        bool empty();

    private:

        std::queue <std::pair <sf::Packet, sf::TcpSocket*>> m_packets;
    };
}