// A log file (logNet.txt, logPing.csv): a boost.iostreams chain onto a file, with an
// optional gzip compressor in front. A log that wasn't enabled (Debug in
// EfzRevival.ini) writes nothing, and errors from the stream are swallowed. 0x70 bytes.
//
// All of it is inline, emitted by the first object that uses each function: the
// constructor, destructor, open and close by ProtocolContext.cpp's; flush and the
// manipulator overload by the network object before it; operator<< by whichever
// object first prints each type. The instantiations for string literals of every
// length are one function (0x4476a0).
#pragma once
#include <exception>
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

class Log {
public:
    // FUNCTION: 0x4325c0
    Log()
        : enabled_(false)
    {
    }

    // FUNCTION: 0x434070 ??1Log@@QAE@XZ
    // (implicit: destroys out_)

    // FUNCTION: 0x43cd20
    void open(const char *path, bool compressed, bool enabled)
    {
        enabled_ = enabled;
        if (enabled_) {
            try {
                if (compressed == true)
                    out_.push(boost::iostreams::gzip_compressor(
                        boost::iostreams::gzip_params(boost::iostreams::gzip::best_compression)));
                out_.push(boost::iostreams::file_sink(path, std::ios::binary));
            } catch (std::exception e) {
            }
        }
    }

    // FUNCTION: 0x438b10
    void close()
    {
        if (enabled_) {
            try {
                out_.reset();
            } catch (std::exception e) {
            }
        }
    }

    // FUNCTION: 0x426310
    void flush()
    {
        if (enabled_) {
            try {
                out_.flush();
            } catch (std::exception e) {
            }
        }
    }

    // FUNCTION: 0x420ca0 ??$?6H@Log@@QAEAAV0@ABH@Z
    // FUNCTION: 0x420e70 ??$?6V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Log@@QAEAAV0@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    // FUNCTION: 0x42a200 ??$?6I@Log@@QAEAAV0@ABI@Z
    // FUNCTION: 0x42a280 ??$?6U?$_Timeobj@D@std@@@Log@@QAEAAV0@ABU?$_Timeobj@D@std@@@Z
    // FUNCTION: 0x42a530 ??$?6V?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@@Log@@QAEAAV0@ABV?$basic_endpoint@Vudp@ip@asio@boost@@@ip@asio@boost@@@Z
    template <class T>
    Log &operator<<(const T &value)
    {
        if (enabled_) {
            try {
                out_ << value;
            } catch (std::exception e) {
            }
        }
        return *this;
    }

    // Calls the manipulator itself (not out_ << manipulator).
    // FUNCTION: 0x422c10 ??6Log@@QAEAAV0@P6AAAV?$basic_ostream@DU?$char_traits@D@std@@@std@@AAV12@@Z@Z
    Log &operator<<(std::ostream &(*manipulator)(std::ostream &))
    {
        if (enabled_) {
            try {
                manipulator(out_);
            } catch (std::exception e) {
            }
        }
        return *this;
    }

private:
    bool enabled_;                              // 0x00
    boost::iostreams::filtering_ostream out_;   // 0x08
};
