// FileTransfer.h : Declaration of the CFileTransfer

#pragma once
#include "resource.h"       // main symbols



#include "COMRPCServer_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFileTransfer

class ATL_NO_VTABLE CFileTransfer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileTransfer, &CLSID_FileTransfer>,
	public IDispatchImpl<IFileTransfer, &IID_IFileTransfer, &LIBID_COMRPCServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFileTransfer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CFileTransfer)
	COM_INTERFACE_ENTRY(IFileTransfer)
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
	STDMETHODIMP CFileTransfer::SendFile(BSTR filePath);
	STDMETHODIMP CFileTransfer::ReceiveFile(BSTR filePath);
};

OBJECT_ENTRY_AUTO(__uuidof(FileTransfer), CFileTransfer)
