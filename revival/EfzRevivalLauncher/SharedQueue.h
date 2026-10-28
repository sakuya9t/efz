// A queue of fixed-size records in named shared memory, between the launcher and the
// EfzRevival.dll it injects into efz.exe. The mapping holds two counters, the number of
// records read and the number written, then a ring of maxElements records; each side
// advances its own counter. The side that creates the mapping zeroes the counters, the
// other opens it. Each queue also has an auto-reset event, "<name>Write", which the DLL
// sets after writing (the launcher waits on the input queue's). 0x28 bytes.
//
// All of it is inline. Its code is in ProtocolContext.cpp's object (0x429a80-0x444580),
// the first to use it, laid out by decorated name, so the record types' names have to
// sort in the order SharedData.h gives. Functions that don't depend on T are one
// function after /OPT:ICF. The annotations list every instantiation the original has,
// by decorated name.
#pragma once
#include <windows.h>
#include <string.h>
#include <atomic>
#include <exception>
#include <sstream>
#include <string>

template <class T>
struct SharedQueueView {
    std::atomic<int> begin;  // 0x00 records read
    std::atomic<int> end;    // 0x04 records written
    T elements[1];           // 0x08 maxElements of them
};

template <class T>
class SharedQueue {
public:
    // FUNCTION: 0x42f310 ??0?$SharedQueue@UColorPalette@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f3e0 ??0?$SharedQueue@UFrameInput@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f4b0 ??0?$SharedQueue@UGameInfo@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f580 ??0?$SharedQueue@UMatchInfo@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f650 ??0?$SharedQueue@UPingStats@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f720 ??0?$SharedQueue@USyncBlock@@@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    // FUNCTION: 0x42f7f0 ??0?$SharedQueue@_N@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@H@Z
    SharedQueue(std::string name, int maxElements)
        : maxElements_(maxElements)
    {
        name_ = name;
        if (!create(name, maxElements, &mapping_, &view_))
            if (!open(name, maxElements, &mapping_, &view_))
                throw std::exception("Failed to create or open existing shared memory");
    }

    // Only ColorPalette's copy is left after folding, at its own place (before its other
    // constructor), although the FrameInput queues are moved into a vector too.
    // FUNCTION: 0x42f2c0 ??0?$SharedQueue@UColorPalette@@@@QAE@$$QAV0@@Z
    SharedQueue(SharedQueue &&other)
        : view_(other.view_), mapping_(other.mapping_), event_(other.event_),
          name_(other.name_), maxElements_(other.maxElements_)
    {
        other.view_ = NULL;
        other.mapping_ = NULL;
        other.event_ = NULL;
    }

    // FUNCTION: 0x433520 ??1?$SharedQueue@UColorPalette@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@UFrameInput@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@UGameInfo@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@UMatchInfo@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@UPingStats@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@USyncBlock@@@@QAE@XZ
    // FUNCTION: 0x433520 ??1?$SharedQueue@_N@@QAE@XZ
    ~SharedQueue()
    {
        UnmapViewOfFile(view_);
        CloseHandle(mapping_);
        CloseHandle(event_);
    }

    // pop and push before the other members: EfzRevival.dll, which lays out header
    // functions by declaration order, has theirs first (the launcher sorts by name).
    // A member function returns any class type through a hidden pointer, the two-byte
    // FrameInput too.
    // FUNCTION: 0x43e240 ?pop@?$SharedQueue@UColorPalette@@@@QAE?AUColorPalette@@XZ
    // FUNCTION: 0x43e2a0 ?pop@?$SharedQueue@UFrameInput@@@@QAE?AUFrameInput@@XZ
    // FUNCTION: 0x43e2f0 ?pop@?$SharedQueue@UMatchInfo@@@@QAE?AUMatchInfo@@XZ
    // FUNCTION: 0x43e350 ?pop@?$SharedQueue@USyncBlock@@@@QAE?AUSyncBlock@@XZ
    T pop()
    {
        checkBounds(view_->begin + 1, view_->end);
        T value = view_->elements[view_->begin % maxElements_];
        ++view_->begin;
        return value;
    }

    // memcpy, not an assignment: assigning a struct copies value into a temporary
    // before the call that loads the index.
    // FUNCTION: 0x43e780 ?push@?$SharedQueue@UColorPalette@@@@QAEXABUColorPalette@@@Z
    // FUNCTION: 0x43e7e0 ?push@?$SharedQueue@UFrameInput@@@@QAEXABUFrameInput@@@Z
    // FUNCTION: 0x43e830 ?push@?$SharedQueue@UGameInfo@@@@QAEXABUGameInfo@@@Z
    // FUNCTION: 0x43e890 ?push@?$SharedQueue@UMatchInfo@@@@QAEXABUMatchInfo@@@Z
    // FUNCTION: 0x43e8f0 ?push@?$SharedQueue@UPingStats@@@@QAEXABUPingStats@@@Z
    // FUNCTION: 0x43e950 ?push@?$SharedQueue@_N@@QAEXAB_N@Z
    void push(const T &value)
    {
        checkBounds(view_->begin, view_->end + 1);
        memcpy(&view_->elements[view_->end % maxElements_], &value, sizeof(T));
        ++view_->end;
    }

    // Empties the queue (both counters back to 0).
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@UColorPalette@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@UFrameInput@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@UGameInfo@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@UMatchInfo@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@UPingStats@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@USyncBlock@@@@QAEXXZ
    // FUNCTION: 0x4384b0 ?clear@?$SharedQueue@_N@@QAEXXZ
    void clear()
    {
        view_->begin = 0;
        view_->end = 0;
    }

    // The event the writer sets ("<name>Write").
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@UColorPalette@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@UFrameInput@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@UGameInfo@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@UMatchInfo@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@UPingStats@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@USyncBlock@@@@QAEPAXXZ
    // FUNCTION: 0x43af70 ?getEvent@?$SharedQueue@_N@@QAEPAXXZ
    HANDLE getEvent()
    {
        return event_;
    }

    // Wakes the reader (EfzRevival.dll signals its input queue every update; 0x100232d0
    // there). The launcher doesn't call it.
    void notify()
    {
        SetEvent(event_);
    }

    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@UColorPalette@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@UFrameInput@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@UGameInfo@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@UMatchInfo@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@UPingStats@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@USyncBlock@@@@QAE_NXZ
    // FUNCTION: 0x43bb50 ?isEmpty@?$SharedQueue@_N@@QAE_NXZ
    bool isEmpty()
    {
        return view_->begin == view_->end;
    }

    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@UColorPalette@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@UFrameInput@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@UGameInfo@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@UMatchInfo@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@UPingStats@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@USyncBlock@@@@QAE_NXZ
    // FUNCTION: 0x43bb80 ?isFull@?$SharedQueue@_N@@QAE_NXZ
    bool isFull()
    {
        return view_->end - view_->begin >= maxElements_;
    }

private:
    // Throws when [begin, end) can't be the queue's contents.
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@UColorPalette@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@UFrameInput@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@UGameInfo@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@UMatchInfo@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@UPingStats@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@USyncBlock@@@@AAEXHH@Z
    // FUNCTION: 0x4380d0 ?checkBounds@?$SharedQueue@_N@@AAEXHH@Z
    void checkBounds(int begin, int end)
    {
        int elements = end - begin;
        if (elements < 0 || elements > maxElements_) {
            std::stringstream message;
            message << "Error: Shared Queue " << name_ << " out of bounds" << std::endl;
            message << "Begin " << begin << " End " << end << " Elements " << elements
                    << " maxElements " << maxElements_ << std::endl;
            throw std::exception(message.str().c_str());
        }
    }

    // FUNCTION: 0x4395a0 ?create@?$SharedQueue@UColorPalette@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UColorPalette@@@@@Z
    // FUNCTION: 0x4396b0 ?create@?$SharedQueue@UFrameInput@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UFrameInput@@@@@Z
    // FUNCTION: 0x4397c0 ?create@?$SharedQueue@UGameInfo@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UGameInfo@@@@@Z
    // FUNCTION: 0x4398d0 ?create@?$SharedQueue@UMatchInfo@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UMatchInfo@@@@@Z
    // FUNCTION: 0x4399e0 ?create@?$SharedQueue@UPingStats@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UPingStats@@@@@Z
    // FUNCTION: 0x439ae0 ?create@?$SharedQueue@USyncBlock@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@USyncBlock@@@@@Z
    // FUNCTION: 0x439be0 ?create@?$SharedQueue@_N@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@_N@@@Z
    bool create(std::string name, int maxElements, HANDLE *mapping, SharedQueueView<T> **view)
    {
        if (maxElements > 0) {
            *mapping = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
                                          maxElements * sizeof(T) + 8, name.c_str());
            if (*mapping != NULL && GetLastError() != ERROR_ALREADY_EXISTS) {
                *view = (SharedQueueView<T> *)MapViewOfFile(*mapping, FILE_MAP_ALL_ACCESS, 0, 0,
                                                            maxElements * sizeof(T) + 8);
                if (*view != NULL) {
                    event_ = CreateEventA(NULL, FALSE, FALSE, (name + "Write").c_str());
                    std::atomic_init(&(*view)->begin, 0);
                    std::atomic_init(&(*view)->end, 0);
                    return true;
                }
            }
        }
        return false;
    }

    // FUNCTION: 0x43ce80 ?open@?$SharedQueue@UColorPalette@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UColorPalette@@@@@Z
    // FUNCTION: 0x43cf70 ?open@?$SharedQueue@UFrameInput@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UFrameInput@@@@@Z
    // FUNCTION: 0x43d050 ?open@?$SharedQueue@UGameInfo@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UGameInfo@@@@@Z
    // FUNCTION: 0x43d130 ?open@?$SharedQueue@UMatchInfo@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UMatchInfo@@@@@Z
    // FUNCTION: 0x43d210 ?open@?$SharedQueue@UPingStats@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@UPingStats@@@@@Z
    // FUNCTION: 0x43d2f0 ?open@?$SharedQueue@USyncBlock@@@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@USyncBlock@@@@@Z
    // FUNCTION: 0x43d3d0 ?open@?$SharedQueue@_N@@AAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPAPAXPAPAU?$SharedQueueView@_N@@@Z
    bool open(std::string name, int maxElements, HANDLE *mapping, SharedQueueView<T> **view)
    {
        if (maxElements > 0) {
            *mapping = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, name.c_str());
            if (*mapping != NULL) {
                *view = (SharedQueueView<T> *)MapViewOfFile(*mapping, FILE_MAP_ALL_ACCESS, 0, 0,
                                                            maxElements * sizeof(T) + 8);
                if (*view != NULL) {
                    event_ = CreateEventA(NULL, FALSE, FALSE, (name + "Write").c_str());
                    return true;
                }
            }
        }
        return false;
    }

    SharedQueueView<T> *view_;  // 0x00
    HANDLE mapping_;            // 0x04
    HANDLE event_;              // 0x08
    std::string name_;          // 0x0c
    int maxElements_;           // 0x24
};
