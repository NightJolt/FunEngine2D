#pragma once

#include "../globals.h"
#include "../pointer.h"
#include "../tools/debugger.h"
#include "packet_storage_t.h"
#include "connection.h"

namespace fun::network {
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

        threadsafe_packet_storage_t& get_packet_storage();

        uint32_t get_client_count();

    private:
        void receive_data();
        void check_connection_requests();
        void close_connection_with_client(uint32_t);

        sf::TcpListener listener;

        uptr_t <sf::TcpSocket> potential_client;
        std::vector <connection_t> clients;

        threadsafe_packet_storage_t packet_storage;
    };
}