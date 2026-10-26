// The table of remote ends.
#include "NetPeers.h"
// OBJECT: 0x41de10 0x420910
#include <mmsystem.h>

// The endpoint's copy constructor and assignment (one function, at 0x405040) are
// emitted by an earlier object; another function here has the same bytes.
// FUNCTION: 0x405040 ??0?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@QAE@ABV0123@@Z
// FUNCTION: 0x405040 ??4?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@QAEAAV0123@ABV0123@@Z
// FUNCTION: 0x405040 ??0?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@QAE@$$QAV0123@@Z
// So are these two of the map's, folded with copies for other maps:
// FUNCTION: 0x408380 ?_Rrotate@?$_Tree@V?$_Tmap_traits@Vaddress@ip@asio@boost@@UPeer@@U?$less@Vaddress@ip@asio@boost@@@std@@V?$allocator@U?$pair@$$CBVaddress@ip@asio@boost@@UPeer@@@std@@@7@$0A@@std@@@std@@IAEXPAU?$_Tree_node@U?$pair@$$CBVaddress@ip@asio@boost@@UPeer@@@std@@PAX@2@@Z
// FUNCTION: 0x42fa60 ??0?$_Tree_iterator@V?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBVaddress@ip@asio@boost@@UPeer@@@std@@@std@@@std@@@std@@QAE@PAU?$_Tree_node@U?$pair@$$CBVaddress@ip@asio@boost@@UPeer@@@std@@PAX@1@PBV?$_Tree_val@U?$_Tree_simple_types@U?$pair@$$CBVaddress@ip@asio@boost@@UPeer@@@std@@@std@@@1@@Z

// FUNCTION: 0x41ebf0 ??0Peer@@QAE@XZ
Peer::Peer()
    : flags(0), lastSeen(0)
{
}

// FUNCTION: 0x41ebc0 ??0Peer@@QAE@ABV?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@HK@Z
Peer::Peer(const Endpoint &endpoint, int flags, DWORD lastSeen)
{
    this->endpoint = endpoint;
    this->flags = flags;
    this->lastSeen = lastSeen;
}

// FUNCTION: 0x41eb70
NetPeers::NetPeers(const Endpoint &target)
    : target(target)
{
}

// FUNCTION: 0x41ed10
NetPeers::~NetPeers()
{
}

// FUNCTION: 0x41f880
void NetPeers::add(const Endpoint &endpoint, int flags)
{
    peers_[endpoint.address()] = Peer(endpoint, flags, timeGetTime());
}

// FUNCTION: 0x41fa50
void NetPeers::clear()
{
    peers_.clear();
}

// FUNCTION: 0x4201b0
bool NetPeers::flagged(const Endpoint &endpoint, int mask)
{
    std::map<boost::asio::ip::address, Peer>::iterator it = peers_.find(endpoint.address());
    if (it != peers_.end())
        return (it->second.flags & mask) >= mask;
    return false;
}

// FUNCTION: 0x420220
bool NetPeers::flaggedAs(const Endpoint &endpoint, int flags)
{
    std::map<boost::asio::ip::address, Peer>::iterator it = peers_.find(endpoint.address());
    if (it != peers_.end())
        return it->second.flags == flags;
    return false;
}

// FUNCTION: 0x420290
std::vector<NetPeers::Endpoint> NetPeers::getFlagged(int mask)
{
    std::vector<Endpoint> endpoints;
    for (std::pair<const boost::asio::ip::address, Peer> peer : peers_) {
        if ((peer.second.flags & mask) >= mask)
            endpoints.push_back(peer.second.endpoint);
    }
    return endpoints;
}

// FUNCTION: 0x420390
std::vector<NetPeers::Endpoint> NetPeers::getKnown()
{
    std::vector<Endpoint> endpoints;
    for (std::pair<const boost::asio::ip::address, Peer> peer : peers_)
        endpoints.push_back(peer.second.endpoint);
    return endpoints;
}

// FUNCTION: 0x420480
std::vector<NetPeers::Endpoint> NetPeers::getRole(int flags)
{
    std::vector<Endpoint> endpoints;
    for (std::pair<const boost::asio::ip::address, Peer> peer : peers_) {
        if (peer.second.flags == flags)
            endpoints.push_back(peer.second.endpoint);
    }
    return endpoints;
}

// FUNCTION: 0x420570
std::vector<NetPeers::Endpoint> NetPeers::getTimedOut(DWORD timeout)
{
    std::vector<Endpoint> endpoints;
    for (std::pair<const boost::asio::ip::address, Peer> peer : peers_) {
        if (timeGetTime() - peer.second.lastSeen > timeout)
            endpoints.push_back(peer.second.endpoint);
    }
    return endpoints;
}

// FUNCTION: 0x420670
bool NetPeers::isKnown(const Endpoint &endpoint)
{
    std::map<boost::asio::ip::address, Peer>::iterator it = peers_.find(endpoint.address());
    return it != peers_.end();
}

// FUNCTION: 0x420850
void NetPeers::remove(const Endpoint &endpoint)
{
    peers_.erase(endpoint.address());
}

// FUNCTION: 0x4208a0
bool NetPeers::touch(const Endpoint &endpoint)
{
    std::map<boost::asio::ip::address, Peer>::iterator it = peers_.find(endpoint.address());
    if (it != peers_.end()) {
        it->second.lastSeen = timeGetTime();
        return true;
    }
    return false;
}
