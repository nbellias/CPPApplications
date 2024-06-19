// dllmain.h : Declaration of module class.

class CCOMwithATLModule : public ATL::CAtlDllModuleT< CCOMwithATLModule >
{
public :
	DECLARE_LIBID(LIBID_COMwithATLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMWITHATL, "{88e80b27-9e2a-44cc-8771-5b58730a1adb}")
};

extern class CCOMwithATLModule _AtlModule;
