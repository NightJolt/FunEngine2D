#pragma once

#include "../globals.h"

#include "packet_storage_t.h"

namespace fun {
    class server_t {
    public:

        server_t();
        ~server_t();

        bool launch(unsigned short);
        void listen();
        void terminate();

        sf::Packet pack(const std::string&);

        void send(const std::string&, sf::TcpSocket*);
        void send_all(const std::string&, sf::TcpSocket* = nullptr);

        void forward(sf::Packet&, sf::TcpSocket*);
        void forward_all(sf::Packet&, sf::TcpSocket* = nullptr);

        packet_storage_t& get_packets();

    private:

        void receive_data();
        void check_connection_requests();
        void close_connection_with_client(uint32_t);

        sf::TcpListener listener;

        sf::TcpSocket* potential_client;
        std::vector <sf::TcpSocket*> clients;

        packet_storage_t packet_storage;
    };
}
