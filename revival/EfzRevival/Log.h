// The DLL's log, logEfz.txt (g_log, EfzRevival.cpp, which opens it in init): the
// launcher's Log (EfzRevivalLauncher/Log.h, a boost.iostreams chain onto a file,
// everything inline) with two more members, width and fill, which the crash handler's
// stack trace uses.
//
// The inline functions are COMDATs at the start of the DLL. Link-time code generation
// specialises them for g_log: those only ever called on g_log don't take their object
// (flush, the constructor, open, close, width, fill), and an operator<< instantiation
// for a string literal of one length used once also has its argument built in
// (0x10013240 "Create replay write\n"). Instantiations for literals of different lengths
// fold into one function when their code is the same: 0x100131d0 is g_log << "..."
// at the start of a statement, 0x10013320 further along a chain (its Log is the
// previous operator<<'s result).
#pragma once
#include <exception>
#include <ostream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
// Nothing uses boost::iostreams::copy, but its header is why every object that includes
// this one has boost.bind's placeholders _1-_9 (and std::ignore) among its static
// initializers, as fourteen of the original's objects do.
#include <boost/iostreams/copy.hpp>

class Log {
public:
    // FUNCTION: 0x10017fc0
    Log()
        : enabled_(false)
    {
    }

    // FUNCTION: 0x10017ff0
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

    // FUNCTION: 0x10018090
    void close()
    {
        if (enabled_) {
            try {
                out_.reset();
            } catch (std::exception e) {
            }
        }
    }

    // FUNCTION: 0x1000dad0
    void flush()
    {
        if (enabled_) {
            try {
                out_.flush();
            } catch (std::exception e) {
            }
        }
    }

    // FUNCTION: 0x10016ad0
    void width(int width)
    {
        if (enabled_)
            out_.width(width);
    }

    // FUNCTION: 0x10016aa0
    void fill(char fill)
    {
        if (enabled_)
            out_.fill(fill);
    }

    // The instantiations (decorated names as the rebuild's map has them; the ones for
    // literals fold, so the length named is whichever copy the link kept):
    // FUNCTION: 0x100131d0 ??$?6$$BY0M@$$CBD@Log@@QAEAAV0@AAY0M@$$CBD@Z
    // FUNCTION: 0x10013240 ??$?6$$BY0BF@$$CBD@Log@@QAEAAV0@AAY0BF@$$CBD@Z
    // FUNCTION: 0x100132b0 ??$?6$$BY0BE@$$CBD@Log@@QAEAAV0@AAY0BE@$$CBD@Z
    // FUNCTION: 0x10013320 ??$?6$$BY0P@$$CBD@Log@@QAEAAV0@AAY0P@$$CBD@Z
    // FUNCTION: 0x100133a0 ??$?6$$BY0BM@$$CBD@Log@@QAEAAV0@AAY0BM@$$CBD@Z
    // FUNCTION: 0x10013410 ??$?6H@Log@@QAEAAV0@ABH@Z
    // FUNCTION: 0x10013530 ??$?6V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Log@@QAEAAV0@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    // FUNCTION: 0x10016fb0 ??$?6_N@Log@@QAEAAV0@AB_N@Z
    // FUNCTION: 0x10017020 ??$?6$$A6AAAVios_base@std@@AAV01@@Z@Log@@QAEAAV0@A6AAAVios_base@std@@AAV12@@Z@Z
    // FUNCTION: 0x1001b320 ??$?6V?$linear_congruential_engine@I$0LMIP@$0A@$0HPPPPPPP@@std@@@Log@@QAEAAV0@ABV?$linear_congruential_engine@I$0LMIP@$0A@$0HPPPPPPP@@std@@@Z
    // FUNCTION: 0x1001b7e0 ??$?6$$BY02$$CBD@Log@@QAEAAV0@AAY02$$CBD@Z
    // FUNCTION: 0x1001b860 ??$?6PAX@Log@@QAEAAV0@ABQAX@Z
    // FUNCTION: 0x1001b8d0 ??$?6$$BY0BL@$$CBD@Log@@QAEAAV0@AAY0BL@$$CBD@Z
    // FUNCTION: 0x1001b940 ??$?6U?$_Smanip@_J@std@@@Log@@QAEAAV0@ABU?$_Smanip@_J@std@@@Z
    // FUNCTION: 0x1001b9c0 ??$?6U?$_Fillobj@D@std@@@Log@@QAEAAV0@ABU?$_Fillobj@D@std@@@Z
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

    // FUNCTION: 0x100180f0 ??6Log@@QAEAAV0@P6AAAV?$basic_ostream@DU?$char_traits@D@std@@@std@@AAV12@@Z@Z
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
    bool enabled_;                                  // 0x00
    boost::iostreams::filtering_ostream out_;       // 0x08
};

extern Log g_log;
