// A periodic timer on the io_service: once started, it calls its callback every period
// milliseconds, each expiry counted from the previous one (so it doesn't drift), until
// it is stopped (the callback isn't called for the cancellation). 0x48 bytes.
//
// All of it is inline, in ProtocolContext.cpp's object; ProtocolContext's five timers
// all start with a boost::bind of one of its handlers, one instantiation of start.
#pragma once
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Timer {
public:
    // FUNCTION: 0x432ab0
    Timer(boost::asio::io_service &io)
        : timer_(io), period_(0), running_(false)
    {
    }

    // FUNCTION: 0x434230 ??1Timer@@QAE@XZ
    // (implicit: destroys callback_, then timer_)

    // repeat isn't used: every timer repeats.
    // FUNCTION: 0x42e7b0 ??$start@V?$bind_t@XV?$mf1@XVProtocolContext@@ABVerror_code@system@boost@@@_mfi@boost@@V?$list2@V?$value@PAVProtocolContext@@@_bi@boost@@U?$arg@$00@3@@_bi@3@@_bi@boost@@@Timer@@QAEXH_N$$QAV?$bind_t@XV?$mf1@XVProtocolContext@@ABVerror_code@system@boost@@@_mfi@boost@@V?$list2@V?$value@PAVProtocolContext@@@_bi@boost@@U?$arg@$00@3@@_bi@3@@_bi@boost@@@Z
    template <class Handler>
    void start(int period, bool repeat, Handler &&callback)
    {
        callback_ = callback;
        period_ = period;
        timer_.expires_from_now(boost::posix_time::milliseconds(period));
        auto handler = boost::bind(&Timer::repeat, this, _1);
        timer_.async_wait(handler);
    }

    // FUNCTION: 0x442220
    void stop()
    {
        timer_.cancel();
    }

private:
    // The error code made and dropped is as in the original.
    // FUNCTION: 0x43f780
    void repeat(const boost::system::error_code &error)
    {
        if (error) {
            boost::system::error_code aborted(boost::asio::error::operation_aborted);
            return;
        }
        callback_(error);
        auto handler = boost::bind(&Timer::repeat, this, _1);
        timer_.expires_at(timer_.expires_at() + boost::posix_time::milliseconds(period_));
        timer_.async_wait(handler);
    }

    boost::asio::deadline_timer timer_;                                // 0x00
    int period_;                                                       // 0x28
    bool running_;                                                     // 0x2c never set
    std::function<void(const boost::system::error_code &)> callback_;  // 0x30
};
