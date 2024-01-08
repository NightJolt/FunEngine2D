#pragma once

#include "../globals.h"
#include "../vec2.h"

#include "defs.h"
#include "packet.h"

namespace fun::rpc {
    struct connection_info_t {
        connection_info_t();
        connection_info_t(ip_t, port_t, port_t);
        explicit connection_info_t(sf::TcpSocket*);
        
        ip_t ip;
        port_t remote_port;
        port_t local_port;
    };

    struct connection_t {
        connection_t();
        connection_t(sf::TcpSocket*);
        ~connection_t();

        connection_t(const connection_t&) = delete;
        connection_t& operator=(const connection_t&) = delete;

        connection_t(connection_t&&) noexcept;
        connection_t& operator=(connection_t&&) noexcept;

        connection_info_t info;
        std::unique_ptr<sf::TcpSocket> socket;
    };

    class connection_stub_t {
    public:
        explicit connection_stub_t(sf::TcpSocket*);

        void send(uint8_t*, uint32_t);
        bool is_valid();

    private:
        sf::TcpSocket* socket;
    };

    class connection_provider_t {
    public:
        void init(port_t);
        void quit();

        addr_t get_addr();

        connection_stub_t get_connection(addr_t);
        bool check_connection(addr_t);

        void check_for_incoming_connections();
        void check_for_incoming_data();

        packet_storage_t& get_packet_storage();

    private:
        addr_t addr;
        sf::TcpListener connection_listener;
        std::unique_ptr<sf::TcpSocket> new_connection;
        std::unordered_map<
            addr_t,
            connection_t,
            decltype([](const addr_t& addr) { return hash(vec2u_t { addr.ip, addr.port }); }),
            decltype([](const addr_t& addr_l, const addr_t& addr_r) { return addr_l.ip == addr_r.ip && addr_l.port == addr_r.port; })
        > connections;
        packet_storage_t packet_storage;
    };
}