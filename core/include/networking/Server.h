#pragma once

#include "../Globals.h"

namespace fun {
    class Server {
    public:

        Server();
        ~Server();

        bool Launch(unsigned short);
        
        void Listen();
        void Close();

    private:

        void ReceiveData();
        void CheckConnectionRequests();
        void CloseConnectionWithClient(size_t);

        sf::TcpSocket* potential_client;
        std::vector <sf::TcpSocket*> clients;

        sf::TcpListener listener;
    };
}