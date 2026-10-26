// STUB
// The netplay session class (constructor 0x422080, "EFZ_NET_SINGLETON"; destructor
// 0x4226e0; run 0x429000) and the address parser 0x4273b0, from the network range
// (0x41dde0-0x429a80). Only what the launcher's front end needs: the layout, which
// decides the __autoclassinit that wmain's object emits (0x418590), and the calls.
#pragma once
#include <boost/asio.hpp>
#include "../Console.h"
#include <windows.h>
#include <string>

class Network {
public:
    Network();                                      // 0x422080
    ~Network();                                     // 0x4226e0
    // mode 0 host, 1 join, 2 spectate; address is "host:port" for 1 and 2.
    void run(int mode, const std::string &address); // 0x429000

private:
    Console console_;                               // 0x00
    boost::asio::io_service io_;                    // 0x24
    int unknown30_;                                 // 0x30
    boost::asio::ip::udp::socket socket_;           // 0x34
    int unknown78_;                                 // 0x78
    char buffer_[0x400];                            // 0x7c
    boost::asio::ip::udp::endpoint remote_;         // 0x47c
    void *unknown498_;                              // 0x498
    int unknown49c_;                                // 0x49c
    HANDLE mutex_;                                  // 0x4a0 EFZ_NET_SINGLETON
    DWORD mutexError_;                              // 0x4a4 GetLastError() after creating it
};

// "host:port" to a UDP endpoint, a default one when isValidAddress rejects it.
boost::asio::ip::udp::endpoint parseEndpoint(const std::string &address); // 0x4273b0
