#include "networking/connection.h"

fun::connection_info_t::connection_info_t() {}

fun::connection_info_t::connection_info_t(sf::TcpSocket* socket) {
    ip = socket->getRemoteAddress().toInteger();
    remote_port = socket->getRemotePort();
    local_port = socket->getLocalPort();
}

fun::connection_info_t::connection_info_t(uint32_t ip, uint8_t rp, uint8_t lp) : ip(ip), remote_port(rp), local_port(lp) {}

fun::connection_t::connection_t(sf::TcpSocket* socket) : socket(socket), info(connection_info_t(socket)) {}