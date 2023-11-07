#pragma once

#include "../globals.h"
#include "../vec2.h"

#include "defs.h"

namespace fun::rpc {
    struct connection_info_t {
        connection_info_t() {}

        explicit connection_info_t(sf::TcpSocket* socket) {
            ip = socket->getRemoteAddress().toInteger();
            remote_port = socket->getRemotePort();
            local_port = socket->getLocalPort();
        }

        connection_info_t(ip_t ip, port_t rp, port_t lp) : ip(ip), remote_port(rp), local_port(lp) {}
        
        ip_t ip;
        port_t remote_port;
        port_t local_port;
    };

    struct connection_t {
        connection_t() : socket(nullptr) {}
        connection_t(sf::TcpSocket* socket) : socket(socket), info(connection_info_t(socket)) {}
        ~connection_t() {
            if (socket) {
                socket->disconnect();
            }
        }

        connection_t(const connection_t&) = delete;
        connection_t& operator=(const connection_t&) = delete;

        connection_t(connection_t&& other) noexcept : info(info), socket(std::exchange(other.socket, nullptr)) {}

        connection_t& operator=(connection_t&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            info = other.info;
            socket = std::exchange(other.socket, nullptr);

            return *this;
        }

        connection_info_t info;
        std::unique_ptr<sf::TcpSocket> socket;
    };

    class connection_stub_t {
    public:
        explicit connection_stub_t(sf::TcpSocket* socket) : socket(socket) {}

        void send(uint8_t* data, uint32_t size) {
            size_t sent = 0;
            while (size != sent) {
                socket->send(data + sent, size - sent, sent);
            }
        }

        bool is_valid() {
            return socket != nullptr && socket->getRemotePort() != 0;
        }

    private:
        sf::TcpSocket* socket;
    };

    class connection_provider_t {
    public:
        void init(port_t port) {
            assert(connection_listener.listen(port) == sf::Socket::Done);

            connection_listener.setBlocking(false);

            new_connection = std::make_unique<sf::TcpSocket>();
        }

        void quit() {
            for (auto& [addr, connection] : connections) {
                connection.socket->disconnect();
            }

            connection_listener.close();
        }

        connection_stub_t get_connection(addr_t addr) {
            if (!connections.contains(addr)) {
                connection_t connection { new sf::TcpSocket() };

                bool is_connected = connection.socket->connect(sf::IpAddress(addr.ip), addr.port) == sf::Socket::Done;
                
                if (!is_connected) {
                    return connection_stub_t { nullptr };
                }

                connection.socket->setBlocking(false);
                connections[addr] = std::move(connection);

                PRINTLN("CONNECTED");
            }

            return connection_stub_t { connections[addr].socket.get() };
        }

        void check_for_incoming_connections() {
            while (true) {
                auto status = connection_listener.accept(*new_connection);

                if (status == sf::Socket::Done) {
                    addr_t addr { new_connection->getRemoteAddress().toInteger(), (port_t)new_connection->getRemotePort() };

                    new_connection->setBlocking(false);
                    connections[addr] = connection_t { new_connection.release() };

                    new_connection = std::make_unique<sf::TcpSocket>();

                    PRINTLN("NEW CONNECTION");
                } else {
                    break;
                }
            }
        }

    private:
        sf::TcpListener connection_listener;
        std::unique_ptr<sf::TcpSocket> new_connection;
        std::unordered_map<
            addr_t,
            connection_t,
            decltype([](const addr_t& addr) { return hash(vec2u_t { addr.ip, addr.port }); }),
            decltype([](const addr_t& addr_l, const addr_t& addr_r) { return addr_l.ip == addr_r.ip && addr_l.port == addr_r.port; })
        > connections;
    };
}