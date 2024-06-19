// dllmain.h : Declaration of module class.

class CCOMRPCServerModule : public ATL::CAtlDllModuleT< CCOMRPCServerModule >
{
public :
	DECLARE_LIBID(LIBID_COMRPCServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMRPCSERVER, "{6e039750-d4c8-4b15-81aa-b91567c2c027}")
};

extern class CCOMRPCServerModule _AtlModule;
