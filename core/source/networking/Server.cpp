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

bool fun::Server::Launch(unsigned short port) {
    return listener.listen(port) == sf::Socket::Done;
}

void fun::Server::Close() {
    listener.close();
}

void fun::Server::Listen() {
    CheckConnectionRequests();
    ReceiveData();
}

void fun::Server::CheckConnectionRequests() {
    next_client:

    auto status = listener.accept(*potential_client);

    if (status == sf::Socket::Done) {
        potential_client->setBlocking(false);
        clients.emplace_back(potential_client);

        potential_client = new sf::TcpSocket;

        goto next_client;
    }
}

void fun::Server::ReceiveData() {
    for (int i = 0; i < clients.size(); i++) {
        sf::Packet packet;

        auto status = clients[i]->receive(packet);

        if (status == sf::Socket::Done) {
            for (int j = 0; j < clients.size(); j++) {
                if (i == j) continue;

                while (clients[j]->send(packet) == sf::Socket::Partial) {} // !
            }

            continue;
        }

        if (status == sf::Socket::Disconnected) {
            CloseConnectionWithClient(i);

            i--;
        }
    }
}

void fun::Server::CloseConnectionWithClient(size_t i) {
    delete clients[i];
    
    std::swap(clients[i], clients.back());
    clients.erase(clients.end() - 1);

    println("Disconnected");
}