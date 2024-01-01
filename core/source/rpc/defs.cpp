#include "rpc/defs.h"

fun::rpc::addr_t::addr_t() : ip(0), port(0) {}
fun::rpc::addr_t::addr_t(ip_t ip, port_t port) : ip(ip), port(port) {}
fun::rpc::addr_t::addr_t(const char* ip, const char* port) : ip(sf::IpAddress(ip).toInteger()), port(atoi(port)) {}
