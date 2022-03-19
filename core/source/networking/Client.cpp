#include "networking/client.h"

fun::client::~client() {
    tcp_socket.disconnect();
}

bool fun::client::connect(const std::string& ip, unsigned short port) {
    tcp_socket.setBlocking(true); // ?

    if (tcp_socket.connect(ip, port) == sf::Socket::Done) {
        tcp_socket.setBlocking(false);

        return true;
    }

    return false;
}

void fun::client::disconnect() {
    tcp_socket.disconnect();
}

void fun::client::receive_data() {
    sf::Packet incoming_packet;

    if (tcp_socket.receive(incoming_packet) == sf::Socket::Done) {
        packets.emplace(incoming_packet);
    }
}

void fun::client::send(const std::string& data) {
    sf::Packet outgoing_packet;

    outgoing_packet << data;

    while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}
}

std::string fun::client::read_next() {
    sf::Packet& packet = packets.front();

    std::string data;
    packet >> data;

    packets.pop();

    return data;
}

int fun::client::packets_left() {
    return packets.size();
}