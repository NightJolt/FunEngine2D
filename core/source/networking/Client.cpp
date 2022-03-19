#include "networking/client.h"

fun::client_t::~client_t() {
    tcp_socket.disconnect();
}

bool fun::client_t::connect(const std::string& ip, unsigned short port) {
    tcp_socket.setBlocking(true); // ?

    if (tcp_socket.connect(ip, port) == sf::Socket::Done) {
        tcp_socket.setBlocking(false);

        return true;
    }

    return false;
}

void fun::client_t::disconnect() {
    tcp_socket.disconnect();
}

void fun::client_t::receive_data() {
    sf::Packet incoming_packet;

    if (tcp_socket.receive(incoming_packet) == sf::Socket::Done) {
        packets.emplace(incoming_packet);
    }
}

void fun::client_t::send(const std::string& data) {
    sf::Packet outgoing_packet;

    outgoing_packet << data;

    while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}
}

std::string fun::client_t::read_next() {
    sf::Packet& packet = packets.front();

    std::string data;
    packet >> data;

    packets.pop();

    return data;
}

int fun::client_t::packets_left() {
    return packets.size();
}