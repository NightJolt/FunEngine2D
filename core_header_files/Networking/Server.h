#pragma once

#include "globals.h"

namespace fun {
    class Server {
    public:

        Server();
        ~Server();

        void Close();

        void Listen();

        bool SetPort(unsigned short);

    private:

        void ListenRequests();
        void ListenData();

        void CollectGarbage();

        static bool IsConnected(const sf::TcpSocket*);

        std::vector <sf::TcpSocket*> clients;

        sf::TcpListener listener;
    };
}