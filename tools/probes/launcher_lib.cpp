// Probe: stream facets, asio internals and boost.iostreams buffers the launcher uses
// (see launcher_std.cpp).
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <locale>
#include <list>
#include <map>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/null.hpp>

template class std::num_get<char>;
template class std::num_get<wchar_t>;
template class std::num_put<char>;
template class std::num_put<wchar_t>;
template class std::numpunct<char>;
template class std::numpunct<wchar_t>;
template class std::time_put<char>;
template class std::time_put<wchar_t>;
template class std::basic_istream<char>;
template class std::basic_ostream<char>;
template class std::basic_iostream<char>;
template class std::basic_ios<char>;
template class std::basic_streambuf<char>;
template class std::basic_istream<wchar_t>;
template class std::basic_ostream<wchar_t>;
template class std::basic_iostream<wchar_t>;
template class std::basic_ios<wchar_t>;
template class std::basic_streambuf<wchar_t>;
template class std::list<std::string>;
template class std::list<std::wstring>;
template class std::map<std::string, std::string>;
template class std::map<std::wstring, std::wstring>;
template class std::map<std::string, int>;
template class std::map<std::wstring, int>;
template class boost::asio::detail::win_iocp_socket_service<boost::asio::ip::udp>;
template class boost::asio::detail::deadline_timer_service<boost::asio::time_traits<boost::posix_time::ptime> >;
template class boost::asio::detail::timer_queue<boost::asio::detail::forwarding_posix_time_traits>;
template class boost::asio::detail::resolver_service<boost::asio::ip::udp>;
template class boost::asio::ip::basic_resolver_query<boost::asio::ip::udp>;
template class boost::asio::ip::basic_resolver_iterator<boost::asio::ip::udp>;
template class boost::asio::ip::basic_resolver_entry<boost::asio::ip::udp>;
template class boost::asio::ip::resolver_service<boost::asio::ip::udp>;
typedef boost::iostreams::basic_gzip_compressor<> gz;
typedef boost::iostreams::basic_file_sink<char> fsink;
typedef boost::iostreams::basic_null_device<char, boost::iostreams::output> nulldev;
template class boost::iostreams::detail::indirect_streambuf<gz, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::detail::indirect_streambuf<fsink, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::detail::indirect_streambuf<nulldev, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::stream_buffer<gz, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::stream_buffer<fsink, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::stream_buffer<nulldev, std::char_traits<char>, std::allocator<char>, boost::iostreams::output>;
template class boost::iostreams::chain<boost::iostreams::output>;
template class boost::iostreams::filtering_stream<boost::iostreams::output>;
template class boost::iostreams::basic_gzip_compressor<>;
template class boost::iostreams::symmetric_filter<boost::iostreams::detail::zlib_compressor_impl<std::allocator<char> >, std::allocator<char> >;
template class boost::iostreams::detail::zlib_compressor_impl<std::allocator<char> >;
template class boost::iostreams::basic_file<char>;
template class boost::iostreams::detail::linked_streambuf<char>;
template class boost::date_time::date_facet<boost::gregorian::date, char>;
template class boost::date_time::time_facet<boost::posix_time::ptime, char>;

void probe2()
{
    std::locale loc;
    std::use_facet<std::codecvt<char, char, int> >(loc);
    std::use_facet<std::codecvt<wchar_t, char, int> >(loc);
    std::wcout << L"x" << std::endl;
    std::cout << "x" << std::endl;
    std::wcin.get();
    std::cin.get();
    std::ofstream o("x"); o << "y";
    std::ifstream i("x"); std::string s; std::getline(i, s);
    std::wofstream wo("x"); wo << L"y";
    std::wifstream wi("x"); std::wstring ws; std::getline(wi, ws);
    boost::gregorian::date d = boost::gregorian::day_clock::local_day();
    std::string ds = boost::gregorian::to_iso_extended_string(d);
    boost::posix_time::ptime t = boost::posix_time::microsec_clock::local_time();
    std::string ts = boost::posix_time::to_iso_string(t);
    std::ostringstream os; os << t << d;
    boost::asio::io_service io;
    boost::asio::ip::udp::resolver r(io);
    boost::asio::ip::udp::resolver::query q("a", "1");
    r.resolve(q);
}
