#include "networking/Client.h"

fun::Client::~Client() {
    tcp_socket.disconnect();
}

bool fun::Client::Connect(const std::string& ip, unsigned short port) {
    tcp_socket.setBlocking(true);

    if (tcp_socket.connect(ip, port) == sf::Socket::Done) {
        tcp_socket.setBlocking(false);

        return true;
    }

    return false;
}

void fun::Client::Disconnect() {
    tcp_socket.disconnect();
}

void fun::Client::Update() {
    sf::Packet incoming_packet;

    if (tcp_socket.receive(incoming_packet) == sf::Socket::Done) {
        packets.emplace(incoming_packet);
    }
}

void fun::Client::Send(const std::string& data) {
    sf::Packet outgoing_packet;

    outgoing_packet << data;

    while (tcp_socket.send(outgoing_packet) == sf::Socket::Partial) {}
}

std::string fun::Client::ReadNext() {
    sf::Packet& packet = packets.front();

    std::string data;
    packet >> data;

    packets.pop();

    return data;
}

int fun::Client::UnreadCount() {
    return packets.size();
}