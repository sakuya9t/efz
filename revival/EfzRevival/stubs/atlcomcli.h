// STUB: ATL's CComPtr, as Visual C++ 2012's atlcomcli.h (ATL 11) defines the members
// Music uses; the toolchain has no ATL. The original included <atlbase.h>: the strings
// of ATL's registrar (L"ForceRemove", L"NoRemove", ...) open the string data of every
// object that includes Music.h. Code from these members is matched by its bytes:
// CComPtr::operator= (0x10020660), CComPtrBase::CoCreateInstance (0x100206b0), ...
#pragma once
#include <windows.h>
#include <objbase.h>

namespace ATL {

template <class T>
class _NoAddRefReleaseOnCComPtr : public T {
private:
    STDMETHOD_(ULONG, AddRef)() = 0;
    STDMETHOD_(ULONG, Release)() = 0;
};

template <class T>
class CComPtrBase {
protected:
    CComPtrBase() throw()
    {
        p = NULL;
    }
    CComPtrBase(_Inout_opt_ T *lp) throw()
    {
        p = lp;
        if (p != NULL)
            p->AddRef();
    }
    void Swap(CComPtrBase &other)
    {
        T *pTemp = p;
        p = other.p;
        other.p = pTemp;
    }

public:
    typedef T _PtrClass;
    ~CComPtrBase() throw()
    {
        if (p)
            p->Release();
    }
    operator T *() const throw()
    {
        return p;
    }
    T &operator*() const
    {
        return *p;
    }
    T **operator&() throw()
    {
        return &p;
    }
    _NoAddRefReleaseOnCComPtr<T> *operator->() const throw()
    {
        return (_NoAddRefReleaseOnCComPtr<T> *)p;
    }
    bool operator!() const throw()
    {
        return (p == NULL);
    }
    bool operator<(_In_opt_ T *pT) const throw()
    {
        return p < pT;
    }
    bool operator!=(_In_opt_ T *pT) const
    {
        return !operator==(pT);
    }
    bool operator==(_In_opt_ T *pT) const throw()
    {
        return p == pT;
    }
    void Release() throw()
    {
        T *pTemp = p;
        if (pTemp) {
            p = NULL;
            pTemp->Release();
        }
    }
    HRESULT CoCreateInstance(_In_ REFCLSID rclsid, _Inout_opt_ LPUNKNOWN pUnkOuter = NULL,
                             _In_ DWORD dwClsContext = CLSCTX_ALL) throw()
    {
        return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(T), (void **)&p);
    }
    template <class Q>
    HRESULT QueryInterface(_Outptr_ Q **pp) const throw()
    {
        return p->QueryInterface(__uuidof(Q), (void **)pp);
    }

    T *p;
};

template <class T>
class CComPtr : public CComPtrBase<T> {
public:
    CComPtr() throw()
    {
    }
    CComPtr(_Inout_opt_ T *lp) throw()
        : CComPtrBase<T>(lp)
    {
    }
    CComPtr(_Inout_ const CComPtr<T> &lp) throw()
        : CComPtrBase<T>(lp.p)
    {
    }
    T *operator=(_Inout_opt_ T *lp) throw()
    {
        if (*this != lp) {
            CComPtr(lp).Swap(*this);
        }
        return *this;
    }
    T *operator=(_Inout_ const CComPtr<T> &lp) throw()
    {
        if (*this != lp) {
            CComPtr(lp).Swap(*this);
        }
        return *this;
    }
};

}  // namespace ATL

using namespace ATL;
