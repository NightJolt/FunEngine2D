#include "networking/Server.h"

fun::Server::Server() {
    listener.setBlocking(false);

    potential_client = new sf::TcpSocket;
}

fun::Server::~Server() {
    for (auto* client : clients) {
        delete client;
    }

    Close();
}

bool fun::Server::SetPort(unsigned short port) {
    return listener.listen(port) == sf::Socket::Done;
}

void fun::Server::Close() {
    listener.close();
}

void fun::Server::Listen() {
    CheckDisconnectedClients();
    CheckConnectionRequests();
    ReceiveData();
}

void fun::Server::CheckDisconnectedClients() {
    for (int i = 0; i < clients.size(); i++) {
        //std::cout << "Connection status for " << i << " : " << clients[i]->getRemoteAddress() << ", " << clients[i]->getRemotePort() << std::endl;

        if (!IsConnected(clients[i])) {
            //std::cout << "Disconnected " << i << std::endl;

            delete clients[i];

            std::swap(clients[i], clients.back());
            clients.erase(clients.end() - 1);
        }
    }
}

void fun::Server::CheckConnectionRequests() {
    next_client:

    if (listener.accept(*potential_client) == sf::Socket::Done) {
        potential_client->setBlocking(false);
        clients.emplace_back(potential_client);

        potential_client = new sf::TcpSocket;

        goto next_client;
    }
}

void fun::Server::ReceiveData() {
    for (int i = 0; i < clients.size() - 1; i++) {
        sf::Packet packet;

        if (clients[i]->receive(packet) == sf::Socket::Done) {
            for (int j = 0; j < clients.size(); j++) {
                if (i == j) continue;

                while (clients[j]->send(packet) == sf::Socket::Partial) {} // !
            }
        }
    }
}

bool fun::Server::IsConnected(const sf::TcpSocket* socket) {
    return socket->getRemoteAddress() != sf::IpAddress::None; // todo: not working
}