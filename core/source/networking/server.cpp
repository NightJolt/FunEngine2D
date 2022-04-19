#include "networking/server.h"

fun::server_t::server_t() {
    listener.setBlocking(false);

    potential_client = new sf::TcpSocket;
}

fun::server_t::~server_t() {
    for (auto* client : clients) {
        delete client;
    }

    terminate();
}

bool fun::server_t::launch(unsigned short port) {
    return listener.listen(port) == sf::Socket::Done;
}

void fun::server_t::terminate() {
    listener.close();
}

void fun::server_t::listen() {
    check_connection_requests();
    receive_data();
}

void fun::server_t::check_connection_requests() {
    next_client:

    auto status = listener.accept(*potential_client);

    if (status == sf::Socket::Done) {
        potential_client->setBlocking(false);
        clients.emplace_back(potential_client);

        potential_client = new sf::TcpSocket;

        goto next_client;
    }
}

void fun::server_t::receive_data() {
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
            close_connection_with_client(i);

            i--;
        }
    }
}

void fun::server_t::close_connection_with_client(size_t i) {
    delete clients[i];
    
    std::swap(clients[i], clients.back());
    clients.erase(clients.end() - 1);
}
