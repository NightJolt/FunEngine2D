#pragma once

#include "../globals.h"

namespace fun {
    class server {
    public:

        server();
        ~server();

        bool launch(unsigned short);
        void listen();
        void terminate();

    private:

        void receive_data();
        void check_connection_requests();
        void close_connection_with_client(size_t);

        sf::TcpSocket* potential_client;
        std::vector <sf::TcpSocket*> clients;

        sf::TcpListener listener;
    };
}