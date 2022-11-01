#pragma once

#include "../globals.h"

namespace fun::network {
    struct packet_t {
        std::string data;
        sf::TcpSocket* sender;

        // move instead of copy
    };

    class packet_storage_t {
    public:
        void enqueue(const sf::Packet&, sf::TcpSocket*);
        packet_t read();
        bool empty();

    private:
        std::queue <std::pair <sf::Packet, sf::TcpSocket*>> m_packets;
    };

    class threadsafe_packet_storage_t {
    public:
        void enqueue(const sf::Packet&, sf::TcpSocket*);
        packet_t read();
        bool empty();

    private:
        std::mutex m_storage_key;
        std::condition_variable m_storage_cond;

        packet_storage_t m_packet_storage;
    };
}