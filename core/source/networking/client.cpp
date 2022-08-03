#include "networking/client.h"

fun::client_t::client_t() : is_connected(false) {}

fun::client_t::~client_t() {
    disconnect();
}

bool fun::client_t::connect(const std::string& ip, unsigned short port) {
    if (check_connection()) disconnect();

    server.setBlocking(true); // ?

    is_connected = server.connect(ip, port) == sf::Socket::Done;

    if (is_connected) {
        server.setBlocking(false);

        return true;
    }

    return false;
}

void fun::client_t::disconnect() {
    server.disconnect();

    is_connected = false;
}

void fun::client_t::receive() {
    if (!check_connection()) return;

    sf::Packet incoming_packet;

    auto status = server.receive(incoming_packet);

    switch(status) {
        case sf::Socket::Done:
            packet_storage.enqueue(incoming_packet, &server);

            break;
            
        case sf::Socket::Disconnected:
            is_connected = false;

            break;
    }
}

void fun::client_t::send(const std::string& data) {
    if (!check_connection()) return;

    sf::Packet outgoing_packet;

    outgoing_packet << data;

    // while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}

    server.send(outgoing_packet);
}

fun::packet_storage_t& fun::client_t::get_packets() {
    return packet_storage;
}

bool fun::client_t::check_connection() {
    return is_connected;
}