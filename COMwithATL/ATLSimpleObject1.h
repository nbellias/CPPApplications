// ATLSimpleObject1.h : Declaration of the CATLSimpleObject1

#pragma once
#include "resource.h"       // main symbols



#include "COMwithATL_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CATLSimpleObject1

class ATL_NO_VTABLE CATLSimpleObject1 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CATLSimpleObject1, &CLSID_ATLSimpleObject1>,
	public IDispatchImpl<IATLSimpleObject1, &IID_IATLSimpleObject1, &LIBID_COMwithATLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CATLSimpleObject1()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CATLSimpleObject1)
	COM_INTERFACE_ENTRY(IATLSimpleObject1)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	// My methods
	STDMETHOD(PrintHelloWorld)();
	STDMETHOD(CalculateCircleArea)(DOUBLE radius, DOUBLE* area);

};

OBJECT_ENTRY_AUTO(__uuidof(ATLSimpleObject1), CATLSimpleObject1)
