#include "HelloCOM.h"
#include <iostream>

class HelloCOM : public IHello
{
public:
    HelloCOM() : refCount(1) {}

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject)
    {
        if (riid == IID_IUnknown || riid == IID_IHello)
        {
            *ppvObject = static_cast<IHello*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    virtual ULONG STDMETHODCALLTYPE AddRef()
    {
        return InterlockedIncrement(&refCount);
    }

    virtual ULONG STDMETHODCALLTYPE Release()
    {
        ULONG ulRefCount = InterlockedDecrement(&refCount);
        if (0 == ulRefCount)
        {
            delete this;
        }
        return ulRefCount;
    }

    virtual HRESULT STDMETHODCALLTYPE SayHello()
    {
        std::cout << "Hello, COM World!" << std::endl;
        return S_OK;
    }

private:
    ~HelloCOM() {}
    long refCount;
};

HRESULT CreateInstance(REFIID riid, void** ppv)
{
    HelloCOM* pHelloCOM = new HelloCOM();
    if (!pHelloCOM)
        return E_OUTOFMEMORY;

    HRESULT hr = pHelloCOM->QueryInterface(riid, ppv);
    pHelloCOM->Release();
    return hr;
}
