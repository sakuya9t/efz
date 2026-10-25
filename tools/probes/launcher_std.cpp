// Probe: instantiates the standard library, boost.asio, iostreams and date_time
// templates that EfzRevival.exe uses, so that tools/revmatch.py can name their code in
// the original (make revival-names). Nothing here is part of the recovered source.
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/function.hpp>

template class std::basic_string<char>;
template class std::basic_string<wchar_t>;
template class std::basic_stringstream<char>;
template class std::basic_stringstream<wchar_t>;
template class std::basic_ostringstream<char>;
template class std::basic_ostringstream<wchar_t>;
template class std::basic_istringstream<char>;
template class std::basic_istringstream<wchar_t>;
template class std::basic_stringbuf<char>;
template class std::basic_stringbuf<wchar_t>;
template class std::basic_filebuf<char>;
template class std::basic_filebuf<wchar_t>;
template class std::basic_ofstream<char>;
template class std::basic_ifstream<char>;
template class std::basic_fstream<char>;
template class std::vector<std::string>;
template class std::vector<std::wstring>;
template class std::vector<char>;
template class std::vector<unsigned char>;
template class std::vector<int>;
template class std::vector<unsigned int>;
template class boost::asio::basic_datagram_socket<boost::asio::ip::udp>;
template class boost::asio::basic_deadline_timer<boost::posix_time::ptime>;
template class boost::asio::ip::basic_endpoint<boost::asio::ip::udp>;
template class boost::asio::ip::basic_resolver<boost::asio::ip::udp>;
template class boost::asio::datagram_socket_service<boost::asio::ip::udp>;
template class boost::asio::deadline_timer_service<boost::posix_time::ptime>;
template class boost::iostreams::filtering_stream<boost::iostreams::output>;
template class boost::iostreams::basic_gzip_compressor<>;
template class boost::iostreams::basic_file_sink<char>;
template class boost::iostreams::basic_null_device<char, boost::iostreams::output>;

void probe_use()
{
    boost::asio::io_service io;
    boost::asio::ip::udp::socket s(io);
    boost::asio::ip::udp::endpoint ep;
    boost::asio::deadline_timer t(io);
    t.expires_from_now(boost::posix_time::milliseconds(1));
    char buf[16];
    boost::system::error_code ec;
    s.open(boost::asio::ip::udp::v4(), ec);
    s.bind(ep, ec);
    s.send_to(boost::asio::buffer(buf), ep, 0, ec);
    s.receive_from(boost::asio::buffer(buf), ep, 0, ec);
    s.close(ec);
    io.run();
    io.poll();
    io.stop();
    io.reset();
    boost::asio::ip::address::from_string("1.2.3.4");
    boost::asio::ip::address_v6::from_string("::1");
    boost::iostreams::filtering_ostream f;
    f.push(boost::iostreams::gzip_compressor());
    f.push(boost::iostreams::file_sink("x"));
    f << 1;
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    std::string ts = boost::posix_time::to_simple_string(now);
    std::wstringstream ws; ws << 1 << L"x" << 1.0;
    std::stringstream ss; ss << 1 << "x" << 1.0;
    std::thread th([]{});
    std::mutex m; m.lock(); m.unlock();
    std::function<void()> fn = []{};
    std::shared_ptr<int> sp = std::make_shared<int>(1);
}
