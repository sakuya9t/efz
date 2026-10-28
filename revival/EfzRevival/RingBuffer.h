// A ring of the last size_ records of a series, one per frame: the online session's
// save states and sounds, the replay session's states. All of it is inline.
#pragma once
#include <limits.h>
#include <vector>

// Indexed by frame number modulo its size. 0x10 bytes. Its functions don't depend on T
// once compiled, so identical instantiations fold into one (the constructors all are
// 0x100228b0), and link-time code generation builds each instantiation's only size
// into resize.
template <class T>
class RingBuffer {
public:
    // FUNCTION: 0x100228b0 ??0?$RingBuffer@V?$map@GHU?$less@G@std@@V?$allocator@U?$pair@$$CBGH@std@@@2@@std@@@@QAE@XZ
    // FUNCTION: 0x100228b0 ??0?$RingBuffer@VSaveState@@@@QAE@XZ
    RingBuffer()
        : size_(0)
    {
    }

    // FUNCTION: 0x100228d0 ?resize@?$RingBuffer@V?$map@GHU?$less@G@std@@V?$allocator@U?$pair@$$CBGH@std@@@2@@std@@@@QAEXH@Z
    // FUNCTION: 0x100229c0 ?resize@?$RingBuffer@VSaveState@@@@QAEXH@Z
    // FUNCTION: 0x1002cc10 ?resize@?$RingBuffer@UReplayState@@@@QAEXH@Z
    void resize(int size)
    {
        size_ = size;
        data_.resize(size);
    }

    // Written out, not implicit: the original has the destructors among the class's
    // header functions, after resize's and before operator[]'s (an implicit one comes
    // out where it is first needed instead).
    // FUNCTION: 0x100228e0 ??1?$RingBuffer@V?$map@GHU?$less@G@std@@V?$allocator@U?$pair@$$CBGH@std@@@2@@std@@@@QAE@XZ
    // FUNCTION: 0x100229d0 ??1?$RingBuffer@VSaveState@@@@QAE@XZ
    ~RingBuffer()
    {
    }

    // The replay session's loop bound (ICF-folded with std::ios_base::rdstate).
    int size()
    {
        return size_;
    }

    // FUNCTION: 0x100228f0 ??A?$RingBuffer@V?$map@GHU?$less@G@std@@V?$allocator@U?$pair@$$CBGH@std@@@2@@std@@@@QAEAAV?$map@GHU?$less@G@std@@V?$allocator@U?$pair@$$CBGH@std@@@2@@std@@I@Z
    // FUNCTION: 0x100229e0 ??A?$RingBuffer@VSaveState@@@@QAEAAVSaveState@@I@Z
    // FUNCTION: 0x1002cc30 ??A?$RingBuffer@UReplayState@@@@QAEAAUReplayState@@I@Z
    T &operator[](unsigned int index)
    {
        if (size_ == 0 || index > INT_MAX)
            throw "Error: index out of bounds";
        return data_[(int)index % size_];
    }

private:
    std::vector<T> data_;           // 0x00
    int size_;                      // 0x0c
};
