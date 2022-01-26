#include "networking/Server.h"

fun::Server::Server() {
    listener.setBlocking(false);

    clients.emplace_back(sf::TcpSocket());
}

fun::Server::~Server() {
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
    for (int i = 0; i < clients.size() - 1; i++) {
        //std::cout << "Connection status for " << i << " : " << clients[i]->getRemoteAddress() << ", " << clients[i]->getRemotePort() << std::endl;

        // todo: swap memory with last elementh and then erase
        if (!IsConnected(clients[i])) {
            //std::cout << "Disconnected " << i << std::endl;

            clients.erase(clients.begin() + i);
        }
    }
}

void fun::Server::CheckConnectionRequests() {
    if (listener.accept(clients.back()) == sf::Socket::Done) {
        clients.back().setBlocking(false);
        clients.emplace_back(sf::TcpSocket());
    }
}

void fun::Server::ReceiveData() {
    for (int i = 0; i < clients.size() - 1; i++) {
        sf::Packet packet;

        if (clients[i].receive(packet) == sf::Socket::Done) {
            for (int j = 0; j < clients.size(); j++) {
                if (i == j) continue;

                while (clients[j].send(packet) == sf::Socket::Partial) {} // !
            }
        }
    }
}

bool fun::Server::IsConnected(const sf::TcpSocket& socket) {
    return socket.getRemoteAddress() != sf::IpAddress::None; // todo: not working
}