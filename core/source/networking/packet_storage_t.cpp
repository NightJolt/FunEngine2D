#include "networking/packet_storage_t.h"

void fun::packet_storage_t::enqueue(const sf::Packet& packet, sf::TcpSocket* sender) {
    m_packets.emplace(packet, sender);
}

fun::packet_storage_t::packet_t fun::packet_storage_t::read() {
    auto& item = m_packets.front();
    packet_t packet;

    item.first.operator >> (packet.data);
    packet.sender = item.second;

    m_packets.pop();

    return packet;
}

bool fun::packet_storage_t::empty() {
    return m_packets.empty();
}