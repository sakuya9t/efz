// The netplay session: state switching, the timers and the console thread, the
// queues to EfzRevival.dll, and every message sent and received.
#include "ProtocolContext.h"
// OBJECT: 0x429790 0x444550
#include "GameProcess.h"
#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <mmsystem.h>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <numeric>

// Inline and template functions this object is the first to use, named here so that
// the checks of later objects find them where the link put them, not at an identical
// copy of their own.
// FUNCTION: 0x434ec0 ??E?$_Vector_iterator@V?$_Vector_val@U?$_Simple_types@V?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@@std@@@std@@@std@@QAEAAV01@XZ
// FUNCTION: 0x434c80 ??9ip@asio@boost@@YA_NABV?$basic_endpoint@Vudp@ip@asio@boost@@@012@0@Z
// FUNCTION: 0x444530 _localtime_s
// FUNCTION: 0x444540 _time
// FUNCTION: 0x42a530 ??$?6V?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@@Log@@QAEAAV0@ABV?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@@Z
// And the ones whose link copy is another object's (or another instantiation's) with
// the same bytes:
// FUNCTION: 0x41b0b0 ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@ID@Z
// FUNCTION: 0x421e30 ??0?$deque@HV?$allocator@H@std@@@std@@QAE@XZ
// FUNCTION: 0x421e30 ??0?$deque@USyncBlock@@V?$allocator@USyncBlock@@@std@@@std@@QAE@XZ
// FUNCTION: 0x404f30 ??0?$_String_alloc@$0A@U?$_String_base_types@DV?$allocator@D@std@@@std@@@std@@QAE@ABV?$allocator@D@1@@Z
// FUNCTION: 0x404f30 ??0?$_String_alloc@$0A@U?$_String_base_types@_WV?$allocator@_W@std@@@std@@@std@@QAE@ABV?$allocator@_W@1@@Z
// FUNCTION: 0x41eb50 ??0?$vector@UFrameInput@@V?$allocator@UFrameInput@@@std@@@std@@QAE@XZ
// FUNCTION: 0x41eb50 ??0?$vector@Uheap_entry@?$timer_queue@Uforwarding_posix_time_traits@detail@asio@boost@@@detail@asio@boost@@V?$allocator@Uheap_entry@?$timer_queue@Uforwarding_posix_time_traits@detail@asio@boost@@@detail@asio@boost@@@std@@@std@@QAE@XZ
// FUNCTION: 0x41eb50 ??0?$vector@V?$SharedQueue@UColorPalette@@@@V?$allocator@V?$SharedQueue@UColorPalette@@@@@std@@@std@@QAE@XZ
// FUNCTION: 0x41eb50 ??0?$vector@V?$SharedQueue@UFrameInput@@@@V?$allocator@V?$SharedQueue@UFrameInput@@@@@std@@@std@@QAE@XZ
// FUNCTION: 0x424710 ?asio_handler_deallocate@asio@boost@@YAXPAXIZZ
// FUNCTION: 0x418700 ?begin@?$deque@HV?$allocator@H@std@@@std@@QAE?AV?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@H@std@@@std@@@2@XZ
// FUNCTION: 0x418700 ?begin@?$deque@UFrameInput@@V?$allocator@UFrameInput@@@std@@@std@@QAE?AV?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@UFrameInput@@@std@@@std@@@2@XZ
// FUNCTION: 0x418700 ?begin@?$deque@USyncBlock@@V?$allocator@USyncBlock@@@std@@@std@@QAE?AV?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@USyncBlock@@@std@@@std@@@2@XZ
// FUNCTION: 0x437fa0 ?cancel_timer@?$timer_queue@U?$time_traits@Vptime@posix_time@boost@@@asio@boost@@@detail@asio@boost@@QAEIAAVper_timer_data@?$timer_queue@Uforwarding_posix_time_traits@detail@asio@boost@@@234@AAV?$op_queue@Vwin_iocp_operation@detail@asio@boost@@@234@I@Z
// FUNCTION: 0x424ba0 ?close@?$basic_socket@Vudp@ip@asio@boost@@V?$datagram_socket_service@Vudp@ip@asio@boost@@@34@@asio@boost@@QAEXXZ
// FUNCTION: 0x419150 ?end@?$deque@HV?$allocator@H@std@@@std@@QAE?AV?$_Deque_iterator@V?$_Deque_val@U?$_Deque_simple_types@H@std@@@std@@@2@XZ

// setPlayerName must be declared throw(): the original has no EH state for the two
// wstring temporaries passed to it.
// FUNCTION: 0x432600
ProtocolContext::ProtocolContext(std::unique_ptr<ProtocolState> &&state, const Endpoint &target,
                                 boost::asio::ip::udp::socket &socket)
    : peers(target), config(L"./EfzRevival.ini"), timer(socket.get_io_service()),
      pingTimer(socket.get_io_service()), timeoutTimer(socket.get_io_service()),
      resendTimer(socket.get_io_service()), gameTimer(socket.get_io_service()),
      initQueue("Init", 1), netQueue("Net", 100), syncQueue("Sync", 200), quitQueue("Quit", 1),
      loadMatchQueue("LoadMatch", 100), queueEvent(socket.get_io_service())
{
    log.open("logNet.txt", false, config.debug);
    pingLog.open("logPing.csv", false, config.debug);
    info.seed = timeGetTime();
    unsigned int rollback = std::abs(config.maxRollback);
    if (rollback > 9)
        rollback = 9;
    name = config.name;
    setPlayer(config.player - 1);
    info.seed = timeGetTime();
    this->socket = &socket;
    setPlayerName(L"Player1", 0);
    setPlayerName(L"Player2", 1);
    inputQueues.push_back(SharedQueue<FrameInput>("InputP1", 600));
    inputQueues.push_back(SharedQueue<FrameInput>("InputP2", 600));
    paletteQueues.push_back(SharedQueue<ColorPalette>("PaletteP1", 10));
    paletteQueues.push_back(SharedQueue<ColorPalette>("PaletteP2", 10));
    info.rollback = rollback;
    info.launcher = GetCurrentProcessId();
    syncFrame = -1;
    hosting = false;
    switchState(std::move(state));
    memset(&process, 0, sizeof(process));
    match.wins[0] = 0;
    match.wins[1] = 0;
    match.match = 0;
    info.practiceKeys = config.allowPracticeKeys != 0;
    peers.add(config.holePunchingServer, 4);
}

// FUNCTION: 0x434080
ProtocolContext::~ProtocolContext()
{
    log.close();
    pingLog.close();
}

// FUNCTION: 0x438b80
void ProtocolContext::close()
{
    closeGame();
    socket->get_io_service().stop();
    socket->shutdown(boost::asio::ip::udp::socket::shutdown_both);
    socket->close();
}

// Asks EfzRevival.dll to quit, or kills efz.exe if the request cannot be queued.
// FUNCTION: 0x438f20
void ProtocolContext::closeGame()
{
    log << "Close Efz\n";
    log.flush();
    if (!quitQueue.isFull()) {
        quitQueue.push(true);
        Sleep(100);
    } else {
        TerminateProcess(process.hProcess, 0);
    }
    CloseHandle(process.hProcess);
    inputQueues[0].clear();
    inputQueues[1].clear();
    paletteQueues[0].clear();
    paletteQueues[1].clear();
    initQueue.clear();
    netQueue.clear();
    syncQueue.clear();
    quitQueue.clear();
}

// FUNCTION: 0x438250
bool ProtocolContext::checkSync(int frame)
{
    if (localSyncs.size() > frame && remoteSyncs.size() > frame) {
        bool same = localSyncs[frame] == remoteSyncs[frame];
        syncFrame = frame;
        time_t now = time(NULL);
        tm local;
        localtime_s(&local, &now);
        log << localSyncs.size() << " " << remoteSyncs.size() << " ";
        if (same) {
            log << std::put_time(&local, "%H:%M:%S") << " Checked " << frame << std::endl;
        } else {
            static bool reported = false;
            if (!reported) {
                reported = true;
                console << "Desync detected\n";
                doAlert();
            }
            log << "ERROR:\nLoc " << localSyncs[frame].toString() << "Rem "
                << remoteSyncs[frame].toString() << std::endl;
        }
        log.flush();
        return same;
    }
    return false;
}

// FUNCTION: 0x4393a0
bool ProtocolContext::consumeInput(int player)
{
    bool consumed = false;
    while (!inputQueues[player].isEmpty()) {
        FrameInput input = inputQueues[player].pop();
        inputs[player].push_back(input);
        consumed = true;
    }
    return consumed;
}

// FUNCTION: 0x439430
bool ProtocolContext::consumeLoadMatch()
{
    if (!loadMatchQueue.isEmpty()) {
        match = loadMatchQueue.pop();
        return true;
    }
    return false;
}

// FUNCTION: 0x439490
bool ProtocolContext::consumePalette(ColorPalette &palette, int player)
{
    bool consumed = false;
    if (!paletteQueues[player].isEmpty()) {
        palette = paletteQueues[player].pop();
        consumed = true;
    }
    return consumed;
}

// FUNCTION: 0x439500
bool ProtocolContext::consumeSync()
{
    bool any = false;
    while (!syncQueue.isEmpty()) {
        SyncBlock block = syncQueue.pop();
        if (block.frame == localSyncs.size()) {
            localSyncs.push_back(block);
            checkSync(block.frame);
            any = true;
        }
    }
    return any;
}

// FUNCTION: 0x439ef0
bool ProtocolContext::debug()
{
    return config.debug;
}

// FUNCTION: 0x439f20
int ProtocolContext::deflate(const google::protobuf::MessageLite &message, void *buffer, int size)
{
    google::protobuf::io::ArrayOutputStream output(buffer, size);
    google::protobuf::io::GzipOutputStream::Options options;
    options.format = google::protobuf::io::GzipOutputStream::ZLIB;
    options.compression_level = 9;
    google::protobuf::io::GzipOutputStream stream(&output, options);
    message.SerializeToZeroCopyStream(&stream);
    if (!stream.Close()) {
        log << "Error compressing " << stream.ZlibErrorCode() << "\n";
        return 0;
    }
    return output.ByteCount();
}

// FUNCTION: 0x43af30
// TODO: differs: esi and edi swapped (the original keeps available in esi, frame in edi).
int ProtocolContext::getCount(int frame, int count, int available, int maximum)
{
    if (frame >= available)
        return 0;
    int n = std::min(count, maximum);
    if (available < frame + n)
        n = available - frame;
    return n;
}

// FUNCTION: 0x43a260
void ProtocolContext::doAlert()
{
    std::thread(&ProtocolContext::handleAlert, this).detach();
}

// FUNCTION: 0x43b1b0
void ProtocolContext::handleAlert()
{
    FlashWindow(GetConsoleWindow(), TRUE);
    PlaySoundW((LPCWSTR)SND_ALIAS_SYSTEMASTERISK, NULL, SND_ALIAS_ID);
}

// FUNCTION: 0x43b1e0
void ProtocolContext::handleCommand(std::string command)
{
    state->handleCommand(*this, command);
}

// The console thread: reads one line, hands it to the state on the io_service thread.
// stopConsole wakes it with a key event that reads as "\a".
// FUNCTION: 0x43b250
void ProtocolContext::handleConsole(DWORD inputMode, DWORD outputMode)
{
    command.clear();
    char buffer[0x80];
    memset(buffer, 0, sizeof buffer);
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(input);
    SetConsoleMode(input, inputMode);
    SetConsoleMode(output, outputMode);
    DWORD read;
    ReadConsoleA(input, buffer, sizeof buffer, &read, NULL);
    command = std::string(buffer);
    if (command.compare("\a") != 0)
        socket->get_io_service().post(boost::bind(&ProtocolContext::handleCommand, this, command));
}

// FUNCTION: 0x43b3a0
void ProtocolContext::handleGameTimer(const boost::system::error_code &)
{
    state->handleGameTimer(*this);
}

// FUNCTION: 0x43b3c0
void ProtocolContext::handlePingTimer(const boost::system::error_code &)
{
    std::vector<Endpoint> peers = this->peers.getFlagged(2);
    for (Endpoint peer : peers)
        sendPing(peer);
}

// FUNCTION: 0x43b4b0
void ProtocolContext::handleQueueEvent()
{
    state->handleQueueEvent(*this);
    queueEvent.async_wait(boost::bind(&ProtocolContext::handleQueueEvent, this));
}

// FUNCTION: 0x43b4f0
void ProtocolContext::handleResendTimer(const boost::system::error_code &)
{
    state->handleResendTimer(*this);
}

// FUNCTION: 0x43b510
void ProtocolContext::handleTimeout(const boost::system::error_code &)
{
    std::vector<Endpoint> peers = this->peers.getTimedOut(8000);
    for (Endpoint peer : peers)
        state->handleTimeout(*this, peer);
}

// FUNCTION: 0x43bbb0
bool ProtocolContext::isGameRunning()
{
    DWORD code = (DWORD)-1;
    GetExitCodeProcess(process.hProcess, &code);
    if (code == STILL_ACTIVE)
        return true;
    return false;
}

// FUNCTION: 0x43bbf0
bool ProtocolContext::isOver()
{
    return state->isOver();
}

// FUNCTION: 0x43bc10
bool ProtocolContext::isUpdateAvailable(int version)
{
    return version > REVIVAL_VERSION;
}

// FUNCTION: 0x43bc20
bool ProtocolContext::isValidGame(int game)
{
    return game == 0;
}

// FUNCTION: 0x43bc30
bool ProtocolContext::isValidVersion(int version)
{
    return version == REVIVAL_VERSION;
}

// Starts efz.exe with EfzRevival.dll; its init gets {mode, version} (mode 0 to play, 1
// to spectate).
// FUNCTION: 0x43c110
void ProtocolContext::launch(const std::string &exe, const std::string &dll, int mode)
{
    GameProcess game;
    int args[2];
    args[0] = mode;
    args[1] = REVIVAL_VERSION;
    game.inject(exe, dll, args, sizeof args);
    process = game.getProcessInfo();
    ResumeThread(process.hThread);
    CloseHandle(process.hThread);
}

// FUNCTION: 0x43e580
void ProtocolContext::provideInit(const GameInfo &info)
{
    initQueue.push(info);
}

// FUNCTION: 0x43e590
void ProtocolContext::provideInput(FrameInput input, int player)
{
    if (!inputQueues[player].isFull()) {
        inputs[player].push_back(input);
        inputQueues[player].push(input);
    }
}

// FUNCTION: 0x43e5f0
bool ProtocolContext::provideLoadMatch()
{
    if (!loadMatchQueue.isFull()) {
        loadMatchQueue.push(match);
        return true;
    }
    return false;
}

// FUNCTION: 0x43e620
void ProtocolContext::provideNet(const PingStats &stats)
{
    if (!netQueue.isFull())
        netQueue.push(stats);
}

// FUNCTION: 0x43e650
void ProtocolContext::providePalette(const ColorPalette &palette, int player)
{
    if (!paletteQueues[player].isFull())
        paletteQueues[player].push(palette);
}

// FUNCTION: 0x43eff0
void ProtocolContext::receiveChangeRole(int role, const Endpoint &from)
{
    if (peers.target != from)
        return;
    state->receiveChangeRole(*this, role, from);
}

// FUNCTION: 0x43f030
void ProtocolContext::receiveConnectConfirm(int game, int version, int player, int role, int seed,
                                            std::wstring name1, std::wstring name2,
                                            bool practiceKeys, const Endpoint &from)
{
    if (!peers.flagged(from, 2)) {
        log << "Discard connect from " << from << std::endl;
        return;
    }
    state->receiveConnectConfirm(*this, game, version, player, role, seed, name1, name2,
                                 practiceKeys, from);
}

// FUNCTION: 0x43f110
void ProtocolContext::receiveConnectRequest(int game, int version, int role, std::wstring name,
                                            bool practiceKeys, const Endpoint &from)
{
    state->receiveConnectRequest(*this, game, version, role, name, practiceKeys, from);
}

// FUNCTION: 0x43f190
void ProtocolContext::receiveDone(int player, const Endpoint &from)
{
    if (peers.flagged(from, 2))
        state->receiveDone(*this, player, from);
}

// FUNCTION: 0x43f1d0
void ProtocolContext::receiveInput(int ack, int frame, const std::deque<FrameInput> &inputs,
                                   const Endpoint &from)
{
    if (peers.flagged(from, 2))
        state->receiveInput(*this, ack, frame, inputs, from);
}

// FUNCTION: 0x43f220
void ProtocolContext::receiveInputAck(int frame, int count, const Endpoint &from)
{
    if (peers.flaggedAs(from, 1))
        state->receiveInputAck(*this, frame, count, from);
}

// FUNCTION: 0x43f260
void ProtocolContext::receivePalette(const ColorPalette &palette, int player, const Endpoint &from)
{
    if (peers.flagged(from, 2))
        state->receivePalette(*this, palette, player, from);
}

// Pings are answered at once (type 3, with the sender's time).
// FUNCTION: 0x43f2a0
void ProtocolContext::receivePing(unsigned int time, const Endpoint &from)
{
    EfzPackets::MessagePing pong;
    pong.set_f3(time);
    send(pong, 3, from, false);
    state->receivePing(*this, from);
}

// FUNCTION: 0x43f340
void ProtocolContext::receivePong(int rtt, const Endpoint &from)
{
    if (peers.flagged(from, 2))
        updatePing(rtt);
    state->receivePong(*this, from);
}

// FUNCTION: 0x43f380
void ProtocolContext::receivePunch(const Endpoint &target, const Endpoint &from)
{
    if (peers.flagged(from, 2) || peers.flagged(from, 4))
        state->receivePunch(*this, target, from);
}

// FUNCTION: 0x43f3d0
void ProtocolContext::receiveQuit(const Endpoint &from)
{
    if (peers.isKnown(from))
        state->receiveQuit(*this, from);
}

// FUNCTION: 0x43f410
void ProtocolContext::receiveRedirect(const Endpoint &target, const Endpoint &from)
{
    if (peers.flagged(from, 2) || peers.flagged(from, 4))
        state->receiveRedirect(*this, target, from);
}

// FUNCTION: 0x43f460
void ProtocolContext::receiveSync(const std::deque<SyncBlock> &blocks, const Endpoint &from)
{
    if (!peers.flagged(from, 2))
        return;
    for (SyncBlock block : blocks) {
        if (block.frame == remoteSyncs.size()) {
            remoteSyncs.push_back(block);
            checkSync(block.frame);
        }
    }
    state->receiveSync(*this, blocks, from);
}

// FUNCTION: 0x43f530
void ProtocolContext::receiveSyncRequest(int frame, int count, const Endpoint &from)
{
    if (peers.flagged(from, 1))
        sendSync(frame, 0, count, from);
}

// FUNCTION: 0x4407c0
void ProtocolContext::send(const google::protobuf::MessageLite &message, char type,
                           const Endpoint &to, bool compress)
{
    static int bytesSerialized = 0;
    static int bytesSent = 0;
    char packet[0x400];
    packet[0] = compress;
    packet[1] = type;
    int size;
    if (compress) {
        size = deflate(message, packet + 2, sizeof packet - 2) + 2;
    } else {
        message.SerializeToArray(packet + 2, sizeof packet - 2);
        size = message.ByteSize() + 2;
    }
    bytesSerialized += message.ByteSize() + 2;
    bytesSent += size;
    if (size >= 0x400) {
        log << "Error: cannot send, message too large" << std::endl;
        log << "Header " << (int)type << " size " << size << std::endl;
        log.flush();
    } else {
        packet[0] = compress;
        packet[1] = type;
        boost::system::error_code error;
        if (socket->send_to(boost::asio::buffer(packet, size), to, 0, error) == 0) {
            log << "Error on send to " << to << " " << error.message() << "\n";
            log << "Header " << (int)type << " size " << size << std::endl;
            log.flush();
        }
    }
}

// FUNCTION: 0x4409f0
void ProtocolContext::sendChangeRole(int role, const Endpoint &to)
{
    EfzPackets::MessageChangeRole message;
    message.set_f1((EfzPackets::Role)role);
    send(message, 8, to, false);
}

// The host's answer: both names, the client's side, the seed.
// FUNCTION: 0x440a80
void ProtocolContext::sendConnectConfirm(int role, const Endpoint &to)
{
    EfzPackets::MessageInit message;
    message.set_f1((EfzPackets::Player)0);
    message.set_f4((EfzPackets::Role)role);
    message.set_f2(0);
    message.set_f3(REVIVAL_VERSION);
    message.set_f5((EfzPackets::Player)remotePlayer);
    message.set_f6(info.seed);
    message.set_f9(info.practiceKeys);
    message.set_f7(info.names[0], sizeof info.names[0]);
    message.set_f8(info.names[1], sizeof info.names[1]);
    send(message, 0, to, true);
}

// FUNCTION: 0x440b80
void ProtocolContext::sendConnectRequest(int role, const Endpoint &to)
{
    EfzPackets::MessageInit message;
    message.set_f1((EfzPackets::Player)1);
    message.set_f4((EfzPackets::Role)role);
    message.set_f2(0);
    message.set_f3(REVIVAL_VERSION);
    message.set_f5((EfzPackets::Player)localPlayer);
    message.set_f6(0);
    message.set_f9(info.practiceKeys);
    message.set_f7(name.c_str(), name.size() * 2);
    send(message, 0, to, true);
}

// FUNCTION: 0x440c70
void ProtocolContext::sendDone(int player, const Endpoint &to)
{
    EfzPackets::MessageDone message;
    message.set_f1((EfzPackets::Player)player);
    send(message, 9, to, false);
}

// FUNCTION: 0x440d00
void ProtocolContext::sendInput(int frame, int count, const Endpoint &to)
{
    if (peers.flaggedAs(to, 1))
        sendInputSpectator(frame, count, to);
    else
        sendInputPlayer(frame, count, to);
}

// FUNCTION: 0x440d40
void ProtocolContext::sendInputAck(int frame, int count, const Endpoint &to)
{
    EfzPackets::MessageInput message;
    message.set_f1((EfzPackets::Player)1);
    message.set_f3(frame);
    message.set_f4(count);
    send(message, 1, to, false);
}

// The local inputs from frame on, with the last remote frame received.
// FUNCTION: 0x440df0
// TODO: differs: ebx and edi swapped (this and the input vector).
void ProtocolContext::sendInputPlayer(int frame, int count, const Endpoint &to)
{
    if ((unsigned int)frame < inputs[localPlayer].size()) {
        int end = frame + getCount(frame, count, inputs[localPlayer].size(), 60);
        EfzPackets::MessageInput message;
        message.set_f1((EfzPackets::Player)0);
        message.set_f2(inputs[remotePlayer].size() - 1);
        message.set_f3(frame);
        for (int i = frame; i < end; i++)
            message.add_f5(&inputs[localPlayer][i], 2);
        send(message, 1, to, true);
    }
}

// Both players' inputs, alternating, and the match being played.
// FUNCTION: 0x440f10
// TODO: differs: the original gives end a stack slot of its own (0x64 bytes of locals);
// here it shares one with a temporary of the min.
void ProtocolContext::sendInputSpectator(int frame, int count, const Endpoint &to)
{
    const unsigned int &available = std::min(inputs[0].size(), inputs[1].size());
    if (frame < (int)available) {
        int n = getCount(frame, count, available, 60);
        EfzPackets::MessageInput message;
        message.set_f1((EfzPackets::Player)0);
        message.set_f2(-1);
        message.set_f3(frame);
        message.set_f4(n);
        message.set_f6(match.match);
        int end = frame + n;
        for (int i = frame; i < end; i++) {
            message.add_f5(&inputs[0][i], 2);
            message.add_f5(&inputs[1][i], 2);
        }
        send(message, 1, to, true);
    }
}

// FUNCTION: 0x441060
void ProtocolContext::sendNatTraversal(unsigned short first, unsigned short last, const Endpoint &to)
{
    if (last - first > 100)
        throw std::exception("Nat traversal port range too large");
    EfzPackets::MessagePing message;
    message.set_f3(0);
    Endpoint port(to);
    for (unsigned short i = first; i <= last; i++) {
        port.port(i);
        send(message, 2, port, false);
    }
}

// FUNCTION: 0x441140
void ProtocolContext::sendPalette(const ColorPalette &palette, int player, int role)
{
    EfzPackets::MessagePalette message;
    message.set_f1((EfzPackets::Player)player);
    message.set_f2(&palette, sizeof palette);
    std::vector<Endpoint> peers = this->peers.getRole(role);
    for (Endpoint peer : peers)
        send(message, 6, peer, true);
}

// FUNCTION: 0x441280
void ProtocolContext::sendPing(const Endpoint &to)
{
    EfzPackets::MessagePing message;
    message.set_f3(timeGetTime());
    send(message, 2, to, false);
}

// Asks the hole punching server to tell target about us.
// FUNCTION: 0x441310
void ProtocolContext::sendPunch(const Endpoint &target, const Endpoint &server)
{
    EfzPackets::MessagePunch message;
    message.set_f1(&target, sizeof target);
    send(message, 10, server, false);
}

// FUNCTION: 0x4413b0
void ProtocolContext::sendQuit(const Endpoint &to)
{
    EfzPackets::MessageQuit message;
    message.set_f1((EfzPackets::Player)0);
    send(message, 5, to, false);
}

// FUNCTION: 0x441440
void ProtocolContext::sendQuitAll()
{
    std::vector<Endpoint> peers = this->peers.getKnown();
    for (Endpoint peer : peers)
        sendQuit(peer);
}

// FUNCTION: 0x441520
void ProtocolContext::sendRedirect(const Endpoint &target, const Endpoint &to)
{
    EfzPackets::MessageRedirect message;
    message.set_f1(&target, sizeof target);
    send(message, 7, to, false);
}

// The local sync data from frame - before to frame + after.
// FUNCTION: 0x4415c0
void ProtocolContext::sendSync(int frame, int before, int after, const Endpoint &to)
{
    if (localSyncs.size() != 0) {
        int first = std::max(0, frame - before);
        int last = std::min((int)localSyncs.size() - 1, frame + after);
        int count = last - first + 1;
        if (count > 0) {
            EfzPackets::MessageSync message;
            message.set_f1((EfzPackets::Player)0);
            int stop = first + count;
            for (int i = first; i < stop; i++)
                message.add_f4(&localSyncs[i], sizeof(SyncBlock));
            send(message, 4, to, true);
        }
    }
}

// FUNCTION: 0x4416e0
void ProtocolContext::sendSyncRequest(int count, const Endpoint &to)
{
    if (count > 0) {
        int frame = syncFrame + 1;
        EfzPackets::MessageSync message;
        message.set_f1((EfzPackets::Player)1);
        message.set_f2(frame);
        message.set_f3(count);
        send(message, 4, to, true);
    }
}

// FUNCTION: 0x441890
void ProtocolContext::setPlayer(int player)
{
    switch (player) {
    case 0:
        localPlayer = 0;
        break;
    case 1:
        localPlayer = 1;
        break;
    default:
        localPlayer = rand() % 2;
        break;
    }
    remotePlayer = (localPlayer + 1) % 2;
    info.player = localPlayer;
}

// FUNCTION: 0x4418e0
void ProtocolContext::setPlayerName(const std::wstring &name, int player) throw()
{
    wchar_t *names = info.names[player];
    memset(names, 0, sizeof info.names[player]);
    std::copy(name.begin(), name.end(), names);
}

// FUNCTION: 0x441de0
void ProtocolContext::startConsole(DWORD inputMode, DWORD outputMode)
{
    if (consoleThread.joinable())
        stopConsole();
    consoleThread = std::thread(&ProtocolContext::handleConsole, this, inputMode, outputMode);
}

// FUNCTION: 0x441e40
void ProtocolContext::startGameTimer(int interval, int)
{
    auto handler = boost::bind(&ProtocolContext::handleGameTimer, this, _1);
    gameTimer.start(interval, true, handler);
}

// FUNCTION: 0x441e80
void ProtocolContext::startPingTimer(int interval, int)
{
    auto handler = boost::bind(&ProtocolContext::handlePingTimer, this, _1);
    pingTimer.start(interval, true, handler);
}

// FUNCTION: 0x441ec0
void ProtocolContext::startQueueEvent()
{
    queueEvent.assign(inputQueues[localPlayer].getEvent());
    queueEvent.async_wait(boost::bind(&ProtocolContext::handleQueueEvent, this));
}

// FUNCTION: 0x441f20
void ProtocolContext::startResendTimer(int interval, int)
{
    auto handler = boost::bind(&ProtocolContext::handleResendTimer, this, _1);
    resendTimer.start(interval, true, handler);
}

// FUNCTION: 0x441f60
void ProtocolContext::startTimeoutTimer(int interval, int)
{
    auto handler = boost::bind(&ProtocolContext::handleTimeout, this, _1);
    timeoutTimer.start(interval, true, handler);
}

// Stops the console thread by typing a line for it.
// FUNCTION: 0x442240
void ProtocolContext::stopConsole()
{
    if (consoleThread.joinable()) {
        KEY_EVENT_RECORD key;
        key.bKeyDown = TRUE;
        key.wRepeatCount = 0;
        key.wVirtualKeyCode = VK_RETURN;
        key.wVirtualScanCode = 0;
        key.uChar.AsciiChar = '\a';
        key.dwControlKeyState = 0;
        INPUT_RECORD record;
        record.EventType = KEY_EVENT;
        record.Event.KeyEvent = key;
        DWORD written;
        WriteConsoleInputA(GetStdHandle(STD_INPUT_HANDLE), &record, 1, &written);
        consoleThread.join();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    }
}

// FUNCTION: 0x4422d0
void ProtocolContext::stopGameTimer()
{
    gameTimer.stop();
}

// FUNCTION: 0x4422e0
void ProtocolContext::stopPingTimer()
{
    pingTimer.stop();
}

// FUNCTION: 0x4422f0
void ProtocolContext::stopQueueEvent()
{
    queueEvent.cancel();
    queueEvent.close();
}

// FUNCTION: 0x442310
void ProtocolContext::stopResendTimer()
{
    resendTimer.stop();
}

// FUNCTION: 0x442320
void ProtocolContext::stopTimeoutTimer()
{
    timeoutTimer.stop();
}

// FUNCTION: 0x442780
void ProtocolContext::switchState(std::unique_ptr<ProtocolState> &&state)
{
    if (!state)
        throw std::exception("Passing null state");
    if (this->state)
        this->state->leave(*this);
    this->state = std::move(state);
    this->state->enter(*this);
}

// FUNCTION: 0x443cc0
// TODO: differs: the original stores ping.last after ping.average, and still keeps
// &ping.average in ebx for the log line; written in that order, this keeps &ping.last
// in ebx instead (76 bytes differ, against 224).
void ProtocolContext::updatePing(int rtt)
{
    pings.push_back(rtt);
    while (pings.size() > 20)
        pings.pop_front();
    std::deque<int>::iterator highest = std::max_element(pings.begin(), pings.end());
    ping.last = rtt;
    ping.average = std::accumulate(pings.begin(), pings.end(), 0) / pings.size();
    ping.minimum = std::min(ping.minimum, rtt);
    ping.maximum = *highest;
    std::deque<int>::iterator lowest = std::min_element(pings.begin(), pings.end());
    log << "Current " << ping.last << " Average " << ping.average << " Min " << *lowest << " Max "
        << *highest << " GlobalMin " << ping.minimum << "\n";
    pingLog << timeGetTime() << "," << rtt << "\n";
}
