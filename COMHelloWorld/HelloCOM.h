#pragma once
#include <windows.h>
#include <unknwn.h>

// {B8576B39-4AD1-4EBC-A859-69A6C08E8A8A}
static const GUID CLSID_HelloCOM =
{ 0xb8576b39, 0x4ad1, 0x4ebc, { 0xa8, 0x59, 0x69, 0xa6, 0xc0, 0x8e, 0x8a, 0x8a } };

// {7D5D7AB3-5EB7-4670-B85D-3C1B38E9614F}
static const GUID IID_IHello =
{ 0x7d5d7ab3, 0x5eb7, 0x4670, { 0xb8, 0x5d, 0x3c, 0x1b, 0x38, 0xe9, 0x61, 0x4f } };

class IHello : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE SayHello() = 0;
};

HRESULT CreateInstance(REFIID riid, void** ppv);