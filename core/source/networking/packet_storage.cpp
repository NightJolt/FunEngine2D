#include "networking/packet_storage.h"



void fun::network::packet_storage_t::enqueue(const sf::Packet& packet, sf::TcpSocket* sender) {
    m_packets.emplace(packet, sender);
}

fun::network::packet_t fun::network::packet_storage_t::read() {
    auto& item = m_packets.front();
    packet_t packet;

    item.first.operator >> (packet.data);
    packet.sender = item.second;

    m_packets.pop();

    return packet;
}

bool fun::network::packet_storage_t::empty() {
    return m_packets.empty();
}



void fun::network::threadsafe_packet_storage_t::enqueue(const sf::Packet& packet, sf::TcpSocket* sender) {
    std::lock_guard <std::mutex> lock(m_storage_key);

    m_packet_storage.enqueue(packet, sender);

    m_storage_cond.notify_one();
}

fun::network::packet_t fun::network::threadsafe_packet_storage_t::read() {
    std::unique_lock <std::mutex> lock(m_storage_key);
    
    m_storage_cond.wait(lock, [this] { return !m_packet_storage.empty(); });

    return m_packet_storage.read();
}

bool fun::network::threadsafe_packet_storage_t::empty() {
    std::lock_guard <std::mutex> lock(m_storage_key);

    return m_packet_storage.empty();
}