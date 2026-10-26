// The netplay session: the current ProtocolState, the peers, the timers, the queues in
// shared memory through which EfzRevival.dll gets the remote inputs and gives the
// local ones, and every message the launcher sends. The network object (Network)
// parses each received datagram and calls the matching receive* function, which hands
// it to the state. 0x760 bytes.
//
// Its object (ProtocolContext.cpp, 0x429790-0x444550) also holds the code of the header
// classes it is the first to use: Log, SharedQueue<T>, Timer, the records of
// SharedData.h, and every template they and the session instantiate.
#pragma once
#include "Version.h"
#include <boost/bind.hpp>
#include "Config.h"
#include "Console.h"
#include "EfzPackets.pb.h"
#include "NetPeers.h"
#include "ProtocolState.h"
#include "Log.h"
#include "SharedData.h"
#include "SharedQueue.h"
#include "Timer.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <windows.h>
#include <deque>
#include <memory>
#include <string>
#include <thread>
#include <vector>

class ProtocolContext {
public:
    typedef boost::asio::ip::udp::endpoint Endpoint;

    ProtocolContext(std::unique_ptr<ProtocolState> &&state, const Endpoint &target,
                    boost::asio::ip::udp::socket &socket);
    ~ProtocolContext();

    void close();
    void closeGame();
    bool checkSync(int frame);
    // Read what EfzRevival.dll wrote; false when there was nothing.
    bool consumeInput(int player);
    bool consumeLoadMatch();
    bool consumePalette(ColorPalette &palette, int player);
    bool consumeSync();
    bool debug();
    int deflate(const google::protobuf::MessageLite &message, void *buffer, int size);
    // Plays the system sound and flashes the console window, on a thread of its own.
    void doAlert();
    void handleAlert();
    void handleCommand(std::string command);
    void handleConsole(DWORD inputMode, DWORD outputMode);
    void handleGameTimer(const boost::system::error_code &error);
    void handlePingTimer(const boost::system::error_code &error);
    void handleQueueEvent();
    void handleResendTimer(const boost::system::error_code &error);
    void handleTimeout(const boost::system::error_code &error);
    bool isGameRunning();
    bool isOver();
    bool isUpdateAvailable(int version);
    bool isValidGame(int game);
    bool isValidVersion(int version);
    // How many of count frames from frame to send, at most maximum, of available.
    int getCount(int frame, int count, int available, int maximum);
    void launch(const std::string &exe, const std::string &dll, int mode);
    // Give EfzRevival.dll what it needs.
    void provideInit(const GameInfo &info);
    void provideInput(FrameInput input, int player);
    bool provideLoadMatch();
    void provideNet(const PingStats &stats);
    void providePalette(const ColorPalette &palette, int player);

    // From Network, one per message (MessageInit is a request or a confirmation,
    // MessageInput inputs or an acknowledgement, MessageSync data or a request).
    void receiveChangeRole(int role, const Endpoint &from);
    void receiveConnectConfirm(int game, int version, int player, int role, int seed,
                               std::wstring name1, std::wstring name2, bool practiceKeys,
                               const Endpoint &from);
    void receiveConnectRequest(int game, int version, int role, std::wstring name,
                               bool practiceKeys, const Endpoint &from);
    void receiveDone(int player, const Endpoint &from);
    void receiveInput(int ack, int frame, const std::deque<FrameInput> &inputs,
                      const Endpoint &from);
    void receiveInputAck(int frame, int count, const Endpoint &from);
    void receivePalette(const ColorPalette &palette, int player, const Endpoint &from);
    void receivePing(unsigned int time, const Endpoint &from);
    void receivePong(int rtt, const Endpoint &from);
    void receivePunch(const Endpoint &target, const Endpoint &from);
    void receiveQuit(const Endpoint &from);
    void receiveRedirect(const Endpoint &target, const Endpoint &from);
    void receiveSync(const std::deque<SyncBlock> &blocks, const Endpoint &from);
    void receiveSyncRequest(int frame, int count, const Endpoint &from);

    // Sends a message with a two-byte header (type, compressed) to an endpoint.
    // Types: 0 Init, 1 Input, 2 Ping, 3 Ping reply, 4 Sync, 5 Quit, 6 Palette,
    // 7 Redirect, 8 ChangeRole, 9 Done, 10 Punch.
    void send(const google::protobuf::MessageLite &message, char type, const Endpoint &to,
              bool compress);
    void sendChangeRole(int role, const Endpoint &to);
    void sendConnectConfirm(int role, const Endpoint &to);
    void sendConnectRequest(int role, const Endpoint &to);
    void sendDone(int player, const Endpoint &to);
    void sendInput(int frame, int count, const Endpoint &to);
    void sendInputAck(int frame, int count, const Endpoint &to);
    void sendInputPlayer(int frame, int count, const Endpoint &to);
    void sendInputSpectator(int frame, int count, const Endpoint &to);
    // Pings every port of to's address in [first, last], at most 100.
    void sendNatTraversal(unsigned short first, unsigned short last, const Endpoint &to);
    void sendPalette(const ColorPalette &palette, int player, int role);
    void sendPing(const Endpoint &to);
    void sendPunch(const Endpoint &target, const Endpoint &server);
    void sendQuit(const Endpoint &to);
    void sendQuitAll();
    void sendRedirect(const Endpoint &target, const Endpoint &to);
    void sendSync(int frame, int before, int after, const Endpoint &to);
    void sendSyncRequest(int count, const Endpoint &to);
    // 0 or 1, or anything else for a random side.
    void setPlayer(int player);
    // throw(): the constructor's calls with string temporaries have no EH state.
    void setPlayerName(const std::wstring &name, int player) throw();
    // The console input thread, and the timers driving the state.
    void startConsole(DWORD inputMode, DWORD outputMode);
    void startGameTimer(int interval, int unused = 0);
    void startPingTimer(int interval, int unused = 0);
    void startQueueEvent();
    void startResendTimer(int interval, int unused = 0);
    void startTimeoutTimer(int interval, int unused = 0);
    void stopConsole();
    void stopGameTimer();
    void stopPingTimer();
    void stopQueueEvent();
    void stopResendTimer();
    void stopTimeoutTimer();
    // Replaces the current state, calling leave on it and enter on the new one.
    void switchState(std::unique_ptr<ProtocolState> &&state);
    void updatePing(int rtt);

    int localPlayer;                                        // 0x000
    int remotePlayer;                                       // 0x004
    std::wstring name;                                      // 0x008 Name in EfzRevival.ini
    std::vector<FrameInput> inputs[2];                      // 0x020 every frame's input
    GameInfo info;                                          // 0x038
    PingStats ping;                                         // 0x14c
    std::vector<SharedQueue<FrameInput> > inputQueues;      // 0x15c "InputP1", "InputP2"
    PROCESS_INFORMATION process;                            // 0x168 efz.exe
    Log log;                                                // 0x178 logNet.txt
    NetPeers peers;                                         // 0x1e8
    MatchInfo match;                                        // 0x20c
    std::deque<int> pings;                                  // 0x218 round trip times
    bool hosting;                                           // 0x22c
    Config config;                                          // 0x230
    boost::asio::ip::udp::socket *socket;                   // 0x404
    int unknown408[4];                                      // 0x408
    std::unique_ptr<ProtocolState> state;                   // 0x418
    std::deque<SyncBlock> localSyncs;                       // 0x41c
    std::deque<SyncBlock> remoteSyncs;                      // 0x430
    Timer timer;                                            // 0x448 unused
    Timer pingTimer;                                        // 0x490
    Timer timeoutTimer;                                     // 0x4d8
    Timer resendTimer;                                      // 0x520
    Timer gameTimer;                                        // 0x568
    Console console;                                        // 0x5b0
    std::vector<SharedQueue<ColorPalette> > paletteQueues;  // 0x5d4 "PaletteP1", "PaletteP2"
    SharedQueue<GameInfo> initQueue;                        // 0x5e0 "Init"
    SharedQueue<PingStats> netQueue;                        // 0x608 "Net"
    SharedQueue<SyncBlock> syncQueue;                       // 0x630 "Sync"
    SharedQueue<bool> quitQueue;                            // 0x658 "Quit"
    SharedQueue<MatchInfo> loadMatchQueue;                  // 0x680 "LoadMatch"
    std::thread consoleThread;                              // 0x6a8
    std::string command;                                    // 0x6b0 the line read
    int syncFrame;                                          // 0x6c8
    Log pingLog;                                            // 0x6d0 logPing.csv
    boost::asio::windows::object_handle queueEvent;         // 0x740
};
