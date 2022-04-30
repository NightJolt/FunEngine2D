#include "networking/client.h"

fun::client_t::~client_t() {
    server.disconnect();
}

bool fun::client_t::connect(const std::string& ip, unsigned short port) {
    server.setBlocking(true); // ?

    if (server.connect(ip, port) == sf::Socket::Done) {
        server.setBlocking(false);

        return true;
    }

    return false;
}

void fun::client_t::disconnect() {
    server.disconnect();
}

void fun::client_t::receive() {
    sf::Packet incoming_packet;

    if (server.receive(incoming_packet) == sf::Socket::Done) {
        packet_storage.enqueue(incoming_packet, &server);
    }
}

void fun::client_t::send(const std::string& data) {
    sf::Packet outgoing_packet;

    outgoing_packet << data;

    // while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}

    server.send(outgoing_packet);
}

fun::packet_storage_t& fun::client_t::get_packets() {
    return packet_storage;
}
