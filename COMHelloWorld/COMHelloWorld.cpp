#include "HelloCOM.h"
#include <iostream>

int main()
{
    // Initialize COM library
    CoInitialize(nullptr);
    
    IHello* pHello = nullptr;
    HRESULT hr = CreateInstance(IID_IHello, (void**)&pHello);
    // The following line cannot be used as WE DO NOT USE A DLL
    // If we try to use it, we will get an error message
    // "Failed to create COM instance." as
    // SUCCEEDED(hr) fails.
    // HRESULT hr = CoCreateInstance(CLSID_HelloCOM, nullptr, CLSCTX_INPROC_SERVER, IID_IHello, (void**)&pHello);


    if (SUCCEEDED(hr))
    {
        pHello->SayHello();
        pHello->Release();
    }
    else
    {
        std::cout << "Failed to create COM instance." << std::endl;
    }

    // Uninitialize COM library
    CoUninitialize();

    return 0;
}
