#include "networking/server.h"



fun::server_t::server_t() {
    listener.setBlocking(false);

    potential_client = new sf::TcpSocket;
}

fun::server_t::~server_t() {
    for (auto* client : clients) {
        delete client;
    }

    delete potential_client;

    terminate();
}



bool fun::server_t::launch(unsigned short port) {
    return listener.listen(port) == sf::Socket::Done;
}

void fun::server_t::listen() {
    check_connection_requests();
    receive_data();
}

void fun::server_t::terminate() {
    listener.close();
}



sf::Packet fun::server_t::pack(const std::string& data) {
    return sf::Packet().operator << (data);
}

void fun::server_t::send(const std::string& data, sf::TcpSocket* client) {
    sf::Packet packet = pack(data);

    forward(packet, client);
}

void fun::server_t::send_all(const std::string& data, sf::TcpSocket* except) {
    sf::Packet packet = pack(data);

    forward_all(packet, except);
}

void fun::server_t::forward(sf::Packet& packet, sf::TcpSocket* client) {
    // while (client->send(packet) == sf::Socket::Partial) {}

    client->send(packet);

    // if (status == sf::Socket::Disconnected)
}

void fun::server_t::forward_all(sf::Packet& packet, sf::TcpSocket* except) {
    for (auto client : clients) {
        if (except != client) forward(packet, client);
    }
}

fun::packet_storage_t& fun::server_t::get_packets() {
    return packet_storage;
}

uint32_t fun::server_t::get_client_count() {
    return clients.size();
}



void fun::server_t::receive_data() {
    for (int i = 0; i < clients.size(); i++) {
        sf::Packet packet;

        auto status = clients[i]->receive(packet);

        switch(status) {
            case sf::Socket::Done:
                packet_storage.enqueue(packet, clients[i]);

                break;
                
            case sf::Socket::Disconnected:
                close_connection_with_client(i);

                i--;

                break;
        }
    }
}

void fun::server_t::check_connection_requests() {
    next_client:

    auto status = listener.accept(*potential_client);

    if (status == sf::Socket::Done) {
        potential_client->setBlocking(false);
        clients.emplace_back(potential_client);

        debugger::push_msg("connected: " + potential_client->getRemoteAddress().toString() + " " + std::to_string(potential_client->getRemotePort()) + " " + std::to_string(potential_client->getLocalPort()));

        potential_client = new sf::TcpSocket;

        goto next_client;
    }
}

void fun::server_t::close_connection_with_client(uint32_t i) {
    delete clients[i];
    
    std::swap(clients[i], clients.back());
    clients.erase(clients.end() - 1);

    debugger::push_msg("disconnected: " + clients[i]->getRemoteAddress().toString());
}
