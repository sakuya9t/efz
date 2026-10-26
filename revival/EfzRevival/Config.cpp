// EfzRevival.dll compiles the same Config.cpp as the launcher (and DDRAW.dll): the
// ini keys and the DIK_/BUTTON_ tables are identical. The addresses below are the
// DLL's copies, which link-time code generation laid out in this order.
#include "../EfzRevivalLauncher/Config.cpp"

// FUNCTION: 0x100655a0 Config::readKey
// FUNCTION: 0x10065620 Config::loadPadNames
// FUNCTION: 0x10065d70 Config::loadKeyNames
// FUNCTION: 0x100688d0 Config::readInt
// FUNCTION: 0x10068900 Config::readString
// FUNCTION: 0x10068970 Config::reload
// FUNCTION: 0x10068980 Config::load
// FUNCTION: 0x1006a140 Config::~Config
// FUNCTION: 0x1006a1c0 Config::Config
// FUNCTION: 0x1006a2a0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
// FUNCTION: 0x1006a2e0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
// FUNCTION: 0x1006a630 isValidAddress

// In the DLL (and DDRAW.dll) parseEndpoint sits among Config's functions; the launcher
// defines it in Network.cpp (0x4273b0), which the DLL doesn't compile. TODO: which file
// really holds it decides the layout; settle that at the full link.
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <vector>

// FUNCTION: 0x1006a3b0
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
        endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
        return endpoint;
    } catch (std::exception e) {
        return endpoint;
    }
}
