// DDRAW.dll compiles the same Config.cpp as the launcher and EfzRevival.dll: the ini
// keys and the DIK_/BUTTON_ tables are identical, and its object holds the address
// parser too. The addresses below are DDRAW.dll's copies.
//
// One difference is not in this file: DDRAW.dll's Version.h (an April 2022 build) had
// the suffix L"h!" where the launcher's has L"h!!!" (the static initializer 0x1007e7f0);
// nothing reads it.
#include "../EfzRevivalLauncher/Config.cpp"

// FUNCTION: 0x100020a0 isValidAddress
// FUNCTION: 0x10002530 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
// FUNCTION: 0x10002600 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
// FUNCTION: 0x10002640 Config::Config
// FUNCTION: 0x10002740 Config::~Config
// FUNCTION: 0x100027c0 Config::load
// FUNCTION: 0x10003bb0 Config::reload
// FUNCTION: 0x10003bc0 Config::readString
// FUNCTION: 0x10003c30 Config::readInt
// FUNCTION: 0x10003c60 Config::loadKeyNames
// FUNCTION: 0x100060d0 Config::loadPadNames
// FUNCTION: 0x10006780 Config::readKey

// "host:port" to a UDP endpoint, or the default one when isValidAddress rejects it
// (stubs/Network.h declares it; in DDRAW.dll it is compiled with Config.cpp).
// FUNCTION: 0x100022c0
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
