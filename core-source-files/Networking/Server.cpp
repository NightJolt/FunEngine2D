#include "Networking/Server.h"

fun::Server::Server() {
    listener.setBlocking(false);
}

fun::Server::~Server() {
    Close();
}

void fun::Server::Close() {
    for (auto client : clients) delete client;

    listener.close();
}

bool fun::Server::SetPort(unsigned short port) {
    return listener.listen(port) == sf::Socket::Done;
}

void fun::Server::Listen() {
    CollectGarbage();
    ListenRequests();
    ListenData();
}

void fun::Server::CollectGarbage() {
    for (int i = (int)clients.size() - 1; i >= 0; i--) {
        //std::cout << "Connection status for " << i << " : " << clients[i]->getRemoteAddress() << ", " << clients[i]->getRemotePort() << std::endl;

        if (!IsConnected(clients[i])) {
            //std::cout << "Disconnected " << i << std::endl;

            clients.erase(clients.begin() + i);
        }
    }
}

void fun::Server::ListenRequests() {
    auto* client = new sf::TcpSocket;

    if (listener.accept(*client) == sf::Socket::Done) {
        client->setBlocking(false);
        clients.emplace_back(client);
    } else {
        delete client;
    }
}

void fun::Server::ListenData() {
    for (int i = 0; i < clients.size(); i++) {
        sf::Packet packet;

        if (clients[i]->receive(packet) == sf::Socket::Done) {
            for (int j = 0; j < clients.size(); j++) {
                if (i == j) continue;

                while (clients[j]->send(packet) == sf::Socket::Partial) {} // Busy waiting
            }
        }
    }
}

bool fun::Server::IsConnected(const sf::TcpSocket* socket) {
    return socket->getRemoteAddress() != sf::IpAddress::None; // todo: not working
}