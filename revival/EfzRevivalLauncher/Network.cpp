// The socket, the receive loop and the parsing of datagrams.
#include "Network.h"
// OBJECT: 0x420910 0x429790
#include "ProtocolContext.h"
#include "ProtocolStateClientConnect.h"
#include "ProtocolStateHostConnect.h"
#include "ProtocolStateSpecConnect.h"
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <mmsystem.h>
#include <cstdlib>
#include <vector>

// Functions of this object that have the same bytes as others, named where they are:
// FUNCTION: 0x422560 ??1?$basic_datagram_socket@Vudp@ip@asio@boost@@V?$datagram_socket_service@Vudp@ip@asio@boost@@@34@@asio@boost@@QAE@XZ
// FUNCTION: 0x4225c0 ??1?$basic_socket@Vudp@ip@asio@boost@@V?$datagram_socket_service@Vudp@ip@asio@boost@@@34@@asio@boost@@IAE@XZ
// FUNCTION: 0x426380 ?get@?$placeholder@$00@detail@placeholders@asio@boost@@SAAAU?$arg@$00@5@XZ
// FUNCTION: 0x4263a0 ?get@?$placeholder@$01@detail@placeholders@asio@boost@@SAAAU?$arg@$01@5@XZ

// The output operators for string literals are one function per class, whatever the
// length; the link keeps another object's copy.
// FUNCTION: 0x4476a0 ??$?6$$BY01$$CBD@Log@@QAEAAV0@AAY01$$CBD@Z
// FUNCTION: 0x4476a0 ??$?6$$BY06$$CBD@Log@@QAEAAV0@AAY06$$CBD@Z
// FUNCTION: 0x4476a0 ??$?6$$BY0N@$$CBD@Log@@QAEAAV0@AAY0N@$$CBD@Z
// FUNCTION: 0x4476a0 ??$?6$$BY0O@$$CBD@Log@@QAEAAV0@AAY0O@$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY01$$CBD@Console@@QAEAAV0@AAY01$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY0BC@$$CBD@Console@@QAEAAV0@AAY0BC@$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY0BP@$$CBD@Console@@QAEAAV0@AAY0BP@$$CBD@Z

// And the templates and inlines whose link copy is another object's (or another
// instantiation's) with the same bytes:
// FUNCTION: 0x4014d0 ??$?4W4basic_errors@error@asio@boost@@@error_code@system@boost@@QAEAAV012@W4basic_errors@error@asio@2@@Z
// FUNCTION: 0x40eaa0 ?make_error_code@error@asio@boost@@YA?AVerror_code@system@3@W4basic_errors@123@@Z
// FUNCTION: 0x424f00 ?construct@?$datagram_socket_service@Vudp@ip@asio@boost@@@asio@boost@@QAEXAAUimplementation_type@?$win_iocp_socket_service@Vudp@ip@asio@boost@@@detail@23@@Z
// FUNCTION: 0x42b700 ??$allocate@V?$bind_t@XV?$mf2@XVNetwork@@IABVerror_code@system@boost@@@_mfi@boost@@V?$list3@V?$value@PAVNetwork@@@_bi@boost@@U?$arg@$01@3@U?$arg@$00@3@@_bi@3@@_bi@boost@@@boost_asio_handler_alloc_helpers@@YAPAXIAAV?$bind_t@XV?$mf2@XVNetwork@@IABVerror_code@system@boost@@@_mfi@boost@@V?$list3@V?$value@PAVNetwork@@@_bi@boost@@U?$arg@$01@3@U?$arg@$00@3@@_bi@3@@_bi@boost@@@Z
// FUNCTION: 0x434ef0 ??F?$_List_const_iterator@V?$_List_val@U?$_List_simple_types@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@@std@@@std@@@std@@QAEAAV01@XZ
// FUNCTION: 0x437520 ?__autoclassinit@?$binder2@V?$bind_t@XV?$mf2@XVNetwork@@IABVerror_code@system@boost@@@_mfi@boost@@V?$list3@V?$value@PAVNetwork@@@_bi@boost@@U?$arg@$01@3@U?$arg@$00@3@@_bi@3@@_bi@boost@@Verror_code@system@3@I@detail@asio@boost@@QAEXI@Z
// FUNCTION: 0x4050e0 ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@ABV01@@Z
// FUNCTION: 0x405060 ??0?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@QAE@ABVaddress@123@G@Z
// FUNCTION: 0x41eb50 ??0?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@QAE@XZ
// FUNCTION: 0x404d70 ??$use_facet@V?$ctype@D@std@@@std@@YAABV?$ctype@D@0@ABVlocale@0@@Z
// FUNCTION: 0x41afd0 ??$use_facet@V?$numpunct@D@std@@@std@@YAABV?$numpunct@D@0@ABVlocale@0@@Z
// FUNCTION: 0x401250 ??$?0PBD@?$iterator_range@PBD@boost@@QAE@PBD0@Z
// FUNCTION: 0x401250 ??$?0PB_W@?$iterator_range@PB_W@boost@@QAE@PB_W0@Z
// FUNCTION: 0x4011d0 ??$?0PBD@?$iterator_range_base@PBDUrandom_access_traversal_tag@boost@@@iterator_range_detail@boost@@IAE@PBD0@Z
// FUNCTION: 0x4011d0 ??$?0V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@@?$iterator_range_base@V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@Urandom_access_traversal_tag@boost@@@iterator_range_detail@boost@@IAE@V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@0@Z
// FUNCTION: 0x4011d0 ??$?0PB_W@?$iterator_range_base@PB_WUrandom_access_traversal_tag@boost@@@iterator_range_detail@boost@@IAE@PB_W0@Z
// FUNCTION: 0x4011d0 ??$?0V?$_String_const_iterator@V?$_String_val@U?$_Simple_types@_W@std@@@std@@@std@@@?$iterator_range_base@V?$_String_const_iterator@V?$_String_val@U?$_Simple_types@_W@std@@@std@@@std@@Urandom_access_traversal_tag@boost@@@iterator_range_detail@boost@@IAE@V?$_String_const_iterator@V?$_String_val@U?$_Simple_types@_W@std@@@std@@@std@@0@Z
// FUNCTION: 0x401250 ??$?0V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@@?$iterator_range@V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@@boost@@QAE@V?$_String_iterator@V?$_String_val@U?$_Simple_types@D@std@@@std@@@std@@0@Z
// FUNCTION: 0x42fa60 ??0?$_List_iterator@V?$_List_val@U?$_List_simple_types@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@@std@@@std@@@std@@QAE@PAU?$_List_node@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@PAX@1@PBV?$_List_val@U?$_List_simple_types@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@@std@@@1@@Z
// FUNCTION: 0x42fa40 ??0?$_List_const_iterator@V?$_List_val@U?$_List_simple_types@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@@std@@@std@@@std@@QAE@PAU?$_List_node@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@PAX@1@PBV?$_List_val@U?$_List_simple_types@U?$pair@IUmapped_type@?$reactor_op_queue@I@detail@asio@boost@@@std@@@std@@@1@@Z
// FUNCTION: 0x42a5d0 ??$?8V?$_Vector_iterator@V?$_Vector_val@U?$_Simple_types@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@std@@@std@@V01@@std@@YA_NABV?$move_iterator@V?$_Vector_iterator@V?$_Vector_val@U?$_Simple_types@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@std@@@std@@@0@0@Z
// FUNCTION: 0x420f10 ??$?8V?$allocator@D@std@@V01@@std@@YA_NABU?$_Wrap_alloc@V?$allocator@D@std@@@0@0@Z
// FUNCTION: 0x420f10 ??$?8V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@V01@@std@@YA_NABU?$_Wrap_alloc@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@0@0@Z
// FUNCTION: 0x401540 ??$?9V?$_Vector_iterator@V?$_Vector_val@U?$_Simple_types@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@std@@@std@@V01@@std@@YA_NABV?$move_iterator@V?$_Vector_iterator@V?$_Vector_val@U?$_Simple_types@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@std@@@std@@@0@0@Z
// FUNCTION: 0x401560 ??$?9V?$allocator@D@std@@V01@@std@@YA_NABU?$_Wrap_alloc@V?$allocator@D@std@@@0@0@Z
// FUNCTION: 0x401560 ??$?9V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@V01@@std@@YA_NABU?$_Wrap_alloc@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@@0@0@Z

// The original also printed an int to the log somewhere that the link dropped as
// unreferenced, which made this object the first with Log's operator<< <int> (0x420ca0)
// and with the std::ostream and num_put code it pulls in. The instantiation stands in
// for that function.
template Log &Log::operator<< <int>(const int &value);

// A name as sent (UTF-16 bytes) to a string.
std::wstring parseName(const std::string &bytes);
// text cut to length characters.
std::wstring truncate(std::wstring text, unsigned int length);

// FUNCTION: 0x422080
Network::Network()
    : mode_(0), socket_(io_), unknown78_(0)
{
    mutex_ = CreateMutexA(NULL, FALSE, "EFZ_NET_SINGLETON");
    mutexError_ = GetLastError();
    context_ = NULL;
}

// FUNCTION: 0x4226e0
Network::~Network()
{
    timeEndPeriod(0);
    try {
        socket_.shutdown(boost::asio::ip::udp::socket::shutdown_both);
        socket_.close();
    } catch (std::exception e) {
    }
    CloseHandle(mutex_);
}

// FUNCTION: 0x421960
template <class Message>
bool Network::parse(Message &message, const char *packet, int size, bool compressed)
{
    try {
        if (compressed) {
            google::protobuf::io::ArrayInputStream input(packet + 2, size - 2);
            google::protobuf::io::GzipInputStream gzip(&input,
                                                       google::protobuf::io::GzipInputStream::ZLIB);
            message.ParseFromZeroCopyStream(&gzip);
        } else {
            message.ParseFromArray(packet + 2, size - 2);
        }
        return true;
    } catch (std::exception e) {
        context_->log << "Parse Error: " << e.what() << std::endl;
        return false;
    }
}

// FUNCTION: 0x4247a0
void Network::asyncReceive()
{
    if (context_ != NULL && !context_->isOver())
        socket_.async_receive_from(boost::asio::buffer(buffer_, sizeof buffer_), remote_,
                                   boost::bind(&Network::receive, this,
                                               boost::asio::placeholders::bytes_transferred,
                                               boost::asio::placeholders::error));
}

// FUNCTION: 0x4264e0
void Network::handlePacket(const char *packet, int size, const Endpoint &from)
{
    if (size < 2)
        return;
    context_->peers.touch(from);
    bool compressed = packet[0] != 0;
    switch (packet[1]) {
    case 0:
        receiveConnect(packet, size, compressed, from);
        break;
    case 1:
        receiveInput(packet, size, compressed, from);
        break;
    case 2:
        receivePing(packet, size, compressed, from);
        break;
    case 3:
        receivePong(packet, size, compressed, from);
        break;
    case 5:
        receiveQuit(packet, size, compressed, from);
        break;
    case 6:
        receivePalette(packet, size, compressed, from);
        break;
    case 4:
        receiveSync(packet, size, compressed, from);
        break;
    case 8:
        receiveChangeRole(packet, size, compressed, from);
        break;
    case 7:
        receiveRedirect(packet, size, compressed, from);
        break;
    case 9:
        receiveDone(packet, size, compressed, from);
        break;
    case 10:
        receivePunch(packet, size, compressed, from);
        break;
    }
}

// FUNCTION: 0x426750
void Network::init(int mode, const std::string &address)
{
    timeBeginPeriod(1);
    Config config(L"./EfzRevival.ini");
    mode_ = mode;
    Endpoint target;
    if (mode == 1 || mode == 2) {
        if (isValidAddress(address)) {
            target = parseEndpoint(address);
        } else {
            console_ << "Invalid address: " << address.c_str() << "\n";
            system("pause");
            return;
        }
    } else if (mode == 0) {
        target.port(config.port);
        if (boost::algorithm::iequals(config.protocol, L"IPv6"))
            target.address(boost::asio::ip::address_v6::loopback());
        else
            target.address(boost::asio::ip::address_v4::loopback());
    }
    Endpoint local;
    try {
        if (target.address().is_v6()) {
            socket_.open(boost::asio::ip::udp::v6());
            local = Endpoint(boost::asio::ip::udp::v6(), config.port);
        } else {
            socket_.open(boost::asio::ip::udp::v4());
            local = Endpoint(boost::asio::ip::udp::v4(), config.port);
        }
        socket_.bind(local);
    } catch (boost::system::system_error e) {
        console_ << e.what() << "\n";
        system("pause");
        return;
    }
    switch (mode) {
    case 0:
        context_ = new ProtocolContext(
            std::unique_ptr<ProtocolStateHostConnect>(new ProtocolStateHostConnect()), target,
            socket_);
        break;
    case 1:
        context_ = new ProtocolContext(
            std::unique_ptr<ProtocolStateClientConnect>(new ProtocolStateClientConnect()),
            target, socket_);
        break;
    case 2:
        context_ = new ProtocolContext(
            std::unique_ptr<ProtocolStateSpecConnect>(new ProtocolStateSpecConnect()), target,
            socket_);
        break;
    }
}

// FUNCTION: 0x4273b0
boost::asio::ip::udp::endpoint parseEndpoint(const std::string &address)
{
    if (!isValidAddress(address))
        return boost::asio::ip::udp::endpoint();
    boost::asio::ip::udp::endpoint endpoint;
    std::vector<std::string> parts;
    std::string text = boost::algorithm::trim_copy(address);
    text.erase(std::remove(text.begin(), text.end(), '['), text.end());
    text.erase(std::remove(text.begin(), text.end(), ']'), text.end());
    boost::algorithm::split(parts, text, boost::algorithm::is_any_of(":"));
    int port = atoi(parts[parts.size() - 1].c_str());
    std::string host = parts[0];
    for (unsigned int i = 1; i < parts.size() - 1; i++) {
        host.append(":");
        host.append(parts[i]);
    }
    try {
        return endpoint = boost::asio::ip::udp::endpoint(
                   boost::asio::ip::address::from_string(host), port);
    } catch (std::exception e) {
        return endpoint;
    }
}

// FUNCTION: 0x427640
std::wstring parseName(const std::string &bytes)
{
    return std::wstring((const wchar_t *)bytes.data(), bytes.size() / 2);
}

// FUNCTION: 0x4279e0
void Network::receive(std::size_t size, const boost::system::error_code &error)
{
    if (error) {
        context_->log << "Recv error: " << error.message() << " src: "
                      << remote_.address().to_string() << "\n";
        context_->log.flush();
    }
    handlePacket(buffer_, size, remote_);
    asyncReceive();
}

// FUNCTION: 0x427af0
void Network::receiveChangeRole(const char *packet, int size, bool compressed,
                                const Endpoint &from)
{
    EfzPackets::MessageChangeRole message;
    if (parse(message, packet, size, compressed))
        context_->receiveChangeRole(message.f1(), from);
}

// FUNCTION: 0x427b90
void Network::receiveConnect(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessageInit message;
    if (parse(message, packet, size, compressed)) {
        std::wstring name1 = message.has_f7() ? truncate(parseName(message.f7()), 20)
                                              : std::wstring(L"None");
        std::wstring name2 = message.has_f8() ? truncate(parseName(message.f8()), 20)
                                              : std::wstring(L"None");
        bool practiceKeys = false;
        if (message.has_f9())
            practiceKeys = message.f9();
        switch (message.f1()) {
        case 0:
            context_->receiveConnectConfirm(message.f2(), message.f3(), message.f5(), message.f4(),
                                            message.f6(), name1, name2, practiceKeys, from);
            break;
        case 1:
            context_->receiveConnectRequest(message.f2(), message.f3(), message.f4(), name1,
                                            practiceKeys, from);
            break;
        }
    }
}

// FUNCTION: 0x427e60
void Network::receiveDone(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessageDone message;
    if (parse(message, packet, size, compressed))
        context_->receiveDone(message.f1(), from);
}

// FUNCTION: 0x427f00
void Network::receiveInput(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessageInput message;
    if (parse(message, packet, size, compressed)) {
        std::deque<FrameInput> inputs;
        for (std::string input : message.f5())
            inputs.push_back(*(const FrameInput *)input.data());
        if (message.has_f6()) {
            int match = message.f6();
            if (context_->match.match != match) {
                context_->match.match = match;
                context_->provideLoadMatch();
            }
        }
        switch (message.f1()) {
        case 0:
            context_->receiveInput(message.f2(), message.f3(), inputs, from);
            break;
        case 1:
            context_->receiveInputAck(message.f3(), message.f4(), from);
            break;
        }
    }
}

// FUNCTION: 0x4280f0
void Network::receivePalette(const char *packet, int size, bool compressed,
                             const Endpoint &from)
{
    EfzPackets::MessagePalette message;
    if (parse(message, packet, size, compressed)) {
        ColorPalette palette = *(const ColorPalette *)message.f2().data();
        context_->receivePalette(palette, message.f1(), from);
    }
}

// FUNCTION: 0x4281d0
void Network::receivePing(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessagePing message;
    if (parse(message, packet, size, compressed))
        context_->receivePing(message.f3(), from);
}

// FUNCTION: 0x428270
void Network::receivePong(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessagePing message;
    if (parse(message, packet, size, compressed))
        context_->receivePong(timeGetTime() - message.f3(), from);
}

// FUNCTION: 0x428320
void Network::receivePunch(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessagePunch message;
    if (parse(message, packet, size, compressed)) {
        Endpoint target = *(const Endpoint *)message.f1().data();
        context_->receivePunch(target, from);
    }
}

// FUNCTION: 0x4283e0
void Network::receiveQuit(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessageQuit message;
    if (parse(message, packet, size, compressed))
        context_->receiveQuit(from);
}

// FUNCTION: 0x428480
void Network::receiveRedirect(const char *packet, int size, bool compressed,
                              const Endpoint &from)
{
    EfzPackets::MessageRedirect message;
    if (parse(message, packet, size, compressed)) {
        Endpoint target = *(const Endpoint *)message.f1().data();
        context_->receiveRedirect(target, from);
    }
}

// FUNCTION: 0x428540
void Network::receiveSync(const char *packet, int size, bool compressed, const Endpoint &from)
{
    EfzPackets::MessageSync message;
    if (parse(message, packet, size, compressed)) {
        std::deque<SyncBlock> blocks;
        for (std::string block : message.f4())
            blocks.push_back(*(const SyncBlock *)block.data());
        switch (message.f1()) {
        case 0:
            context_->receiveSync(blocks, from);
            break;
        case 1:
            context_->receiveSyncRequest(message.f2(), message.f3(), from);
            break;
        }
    }
}

// FUNCTION: 0x429000
void Network::start(int mode, const std::string &address)
{
    if (mutexError_ == ERROR_ALREADY_EXISTS) {
        console_ << "Only one net instance allowed\n";
        system("pause");
        return;
    }
    init(mode, address);
    asyncReceive();
    io_.run();
    if (context_ != NULL) {
        delete context_;
        context_ = NULL;
    }
}

// FUNCTION: 0x429540
std::wstring truncate(std::wstring text, unsigned int length)
{
    if (text.size() > length)
        text.resize(length);
    return text;
}
