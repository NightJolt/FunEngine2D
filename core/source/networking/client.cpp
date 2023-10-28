#include "networking/client.h"

fun::network::client_t::client_t() : is_connected(false) {}

fun::network::client_t::~client_t() {
    disconnect();
}

bool fun::network::client_t::connect(const std::string& ip, unsigned short port) {
    if (check_connection()) disconnect();

    server.setBlocking(true); // ?

    is_connected = server.connect(ip, port) == sf::Socket::Done;

    if (is_connected) {
        server.setBlocking(false);

        return true;
    }

    return false;
}

void fun::network::client_t::disconnect() {
    server.disconnect();

    is_connected = false;
}

void fun::network::client_t::receive() {
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

void fun::network::client_t::send(const std::string& data) {
    if (!check_connection()) return;

    sf::Packet outgoing_packet;

    outgoing_packet << data;

    // while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}

    server.send(outgoing_packet);
}

void fun::network::client_t::send(const uint8_t* data, size_t size) {
    if (!check_connection()) return;

    sf::Packet outgoing_packet;

    outgoing_packet.append(data, size);

    server.send(outgoing_packet);
}

fun::network::packet_storage_t& fun::network::client_t::get_packets() {
    return packet_storage;
}

bool fun::network::client_t::check_connection() {
    return is_connected;
}