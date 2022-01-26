#pragma once

#include "../../../core/include/globals.h"

namespace fun {
    class Server {
    public:

        Server();
        ~Server();

        bool SetPort(unsigned short);

        void Listen();
        void Close();

    private:

        void ReceiveData();

        void CheckConnectionRequests();
        void CheckDisconnectedClients();

        static bool IsConnected(const sf::TcpSocket*);

        sf::TcpSocket* potential_client;
        std::vector <sf::TcpSocket*> clients;

        sf::TcpListener listener;
    };
}