// The netplay session's network side: the UDP socket and the io_service that runs the
// whole session, the receive loop, and the parsing of each datagram into the matching
// ProtocolContext::receive* call. 0x4a8 bytes.
//
// A datagram is a 2-byte header and a protobuf message (EfzPackets.proto): byte 0 is
// non-zero when the message is zlib-compressed, byte 1 its type:
//   0 MessageInit  1 MessageInput  2 MessagePing  3 MessagePing (pong)  4 MessageSync
//   5 MessageQuit  6 MessagePalette  7 MessageRedirect  8 MessageChangeRole
//   9 MessageDone  10 MessagePunch
#pragma once
#include <boost/asio.hpp>
#include "Console.h"
#include <google/protobuf/stubs/common.h>
#include <windows.h>
#include <string>

class ProtocolContext;

class Network {
public:
    typedef boost::asio::ip::udp::endpoint Endpoint;

    Network();
    ~Network();
    // Runs a session until it is over: mode 0 hosts, 1 joins, 2 spectates; address is
    // "host:port" for 1 and 2. Refuses when another launcher's session is running.
    void start(int mode, const std::string &address);

private:
    // Waits for the next datagram (unless the session is over).
    void asyncReceive();
    // Hands a datagram to the receive* function for its type.
    void handlePacket(const char *packet, int size, const Endpoint &from);
    // Reads the ini, opens and binds the socket and creates the session in its first
    // state (HostConnect, ClientConnect or SpecConnect).
    void init(int mode, const std::string &address);
    // Parses a datagram's message, inflating it first when compressed; false (and a line
    // in the log) when protobuf throws.
    template <class Message>
    bool parse(Message &message, const char *packet, int size, bool compressed);
    // The receive handler.
    void receive(std::size_t size, const boost::system::error_code &error);
    void receiveChangeRole(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveConnect(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveDone(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveInput(const char *packet, int size, bool compressed, const Endpoint &from);
    void receivePalette(const char *packet, int size, bool compressed, const Endpoint &from);
    void receivePing(const char *packet, int size, bool compressed, const Endpoint &from);
    void receivePong(const char *packet, int size, bool compressed, const Endpoint &from);
    void receivePunch(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveQuit(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveRedirect(const char *packet, int size, bool compressed, const Endpoint &from);
    void receiveSync(const char *packet, int size, bool compressed, const Endpoint &from);

    Console console_;                               // 0x00
    boost::asio::io_service io_;                    // 0x24
    int mode_;                                      // 0x30
    boost::asio::ip::udp::socket socket_;           // 0x34
    int unknown78_;                                 // 0x78 only ever zeroed
    char buffer_[0x400];                            // 0x7c the datagram being received
    Endpoint remote_;                               // 0x47c and its sender
    ProtocolContext *context_;                      // 0x498
    google::protobuf::LogSilencer silencer_;        // 0x49c
    HANDLE mutex_;                                  // 0x4a0 EFZ_NET_SINGLETON
    DWORD mutexError_;                              // 0x4a4 GetLastError() after creating it
};

// "host:port" (an IPv6 host may be in brackets) to a UDP endpoint; a default one when
// isValidAddress rejects it or the address does not parse.
boost::asio::ip::udp::endpoint parseEndpoint(const std::string &address);
