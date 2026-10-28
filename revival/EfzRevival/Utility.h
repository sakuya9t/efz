// Helpers that Config.cpp, OnlineSession.cpp and TournamentSession.cpp each have a copy
// of (static functions, a header's or pasted): each of the three objects has the same
// first strings (L"None", L"Name", L"Parameters", then isValidAddress's and
// parseEndpoint's four ":"), and the sessions their own to_utf8 pair (0x10073d00 and
// 0x10073cc0, 0x10079d50 and 0x10079d10), in the same order as Config.cpp's. Only
// Config.obj uses the address parser; the sessions' copies of it are dropped. The
// header's name is made up.
#pragma once
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/asio/ip/udp.hpp>

// Unused code the original had here, of which only traces are left: its string literals
// (each of the three objects' strings begin with L"None", L"Name", L"Parameters": the
// arguments of an ini read, which are evaluated right to left), the import of
// GetPrivateProfileStringW (KERNEL32's imports have it before WideCharToMultiByte, which
// to_utf8, defined next, uses first otherwise), wstring's constructor from a buffer and
// a length (with it, Config.obj's header functions have wstring's assign for a buffer
// and a length among the first) and, in Config.obj, the locale ids of narrow and wide
// number output (Config.obj's first four static initializers after the error categories,
// though none of its code prints a number). Link-time code generation drops the function
// itself.
static std::wstring unusedKeyText(const std::wstring &path, int number)
{
    wchar_t buffer[0x100];
    DWORD length = GetPrivateProfileStringW(L"Parameters", L"Name", L"None", buffer, 0x100,
                                            path.c_str());
    std::wstring text(buffer, length);
    std::wstringstream wide;
    wide << text << number;
    std::ostringstream narrow;
    narrow << number;
    return wide.str();
}

// FUNCTION: 0x1006a630
static bool isValidAddress(const std::string &address)
{
    std::vector<std::string> parts;
    std::string text = boost::algorithm::trim_copy(address);
    text.erase(std::remove(text.begin(), text.end(), '['), text.end());
    text.erase(std::remove(text.begin(), text.end(), ']'), text.end());
    boost::algorithm::split(parts, text, boost::algorithm::is_any_of(":"));
    if (parts.size() < 2)
        return false;
    int port = atoi(parts[parts.size() - 1].c_str());
    std::string host = parts[0];
    for (unsigned int i = 1; i < parts.size() - 1; i++) {
        host.append(":");
        host.append(parts[i]);
    }
    try {
        boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    } catch (std::exception e) {
        return false;
    }
    return true;
}

// FUNCTION: 0x1006a3b0
static boost::asio::ip::udp::endpoint parseEndpoint(const std::string &address)
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

// FUNCTION: 0x1006a2e0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
static std::string to_utf8(const wchar_t *text, int length)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, text, length, NULL, 0, NULL, NULL);
    if (size == 0)
        return "";
    std::string result;
    result.resize(size);
    WideCharToMultiByte(CP_UTF8, 0, text, length, (char *)result.c_str(), size, NULL, NULL);
    return result;
}

// FUNCTION: 0x1006a2a0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
static std::string to_utf8(const std::wstring &text)
{
    return to_utf8(text.c_str(), text.size());
}
