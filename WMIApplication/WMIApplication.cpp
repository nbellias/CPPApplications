// WMIApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <comdef.h>
#include <Wbemidl.h>
#include "HWInfo.h"

#pragma comment(lib, "wbemuuid.lib")

using namespace std;

int main()
{
    cout << "WMI Demo\n";

    GetBIOSInfo();
    GetHardwareInfo();

    // Press SPACE BAR to exit
    cout << "\nPress SPACE BAR to exit\n";
    while (true) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            break;
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

void GetBIOSInfo()
{
    HRESULT hres;

    // Initialize COM.
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x"
            << hex << hres << endl;
        return;
    }

    // Set COM security levels.
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );

    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return;
    }

    // Obtain the initial locator to WMI.
    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object. "
            << "Error code = 0x" << hex << hres << endl;
        CoUninitialize();
        return;
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method.
    IWbemServices* pSvc = NULL;

    // Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // WMI namespace.
        NULL,                    // User name. NULL = current user or _bstr_t(L"NikolaosBellias") for a specific user.
        NULL,                    // User password. NULL = current.
        0,                       // Locale. NULL indicates current.
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos).
        0,                       // Context object.
        &pSvc                    // Pointer to IWbemServices proxy.
    );

    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return;
    }

    cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

    // Set security levels on the proxy.
    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set.
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx.
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx.
        NULL,                        // Server principal name.
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx.
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx.
        NULL,                        // Client identity.
        EOAC_NONE                    // Proxy capabilities.
    );

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // Use the IWbemServices pointer to make requests of WMI. For example, get the name of the operating system.
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_BIOS"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for BIOS name failed. "
            << "Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }
    else
    {
        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pEnumerator)
        {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn)
            {
                break;
            }

            VARIANT vtProp;

            // Get the value of the Name property
            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            wcout << " BIOS Name : " << vtProp.bstrVal << endl;
            VariantClear(&vtProp);

            // Get the value of the Manufacturer property
            hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
            wcout << " BIOS Manufacturer : " << vtProp.bstrVal << endl;
            VariantClear(&vtProp);

            // Get the value of the SerialNumber property
            hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
            wcout << " BIOS SerialNumber : " << vtProp.bstrVal << endl;
            VariantClear(&vtProp);

            // Get the value of the Version property
            hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
            wcout << " BIOS Version : " << vtProp.bstrVal << endl;
            VariantClear(&vtProp);

            pclsObj->Release();
        }
    }

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();
}

void GetHardwareInfo()
{
    HRESULT hres;

    // Initialize COM.
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x"
            << hex << hres << endl;
        return;
    }

    // Set COM security levels.
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL
    );

    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return;
    }

    // Obtain the initial locator to WMI.
    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object. "
            << "Error code = 0x" << hex << hres << endl;
        CoUninitialize();
        return;
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method.
    IWbemServices* pSvc = NULL;

    // Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // WMI namespace.
        NULL,                    // User name. NULL = current user.
        NULL,                    // User password. NULL = current.
        0,                       // Locale. NULL indicates current.
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos).
        0,                       // Context object.
        &pSvc                    // Pointer to IWbemServices proxy.
    );

    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return;
    }

    cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

    // Set security levels on the proxy.
    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set.
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx.
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx.
        NULL,                        // Server principal name.
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx.
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx.
        NULL,                        // Client identity.
        EOAC_NONE                    // Proxy capabilities.
    );

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // Function to query and display information from a WMI class
    auto QueryWMIClass = [&](const BSTR query, const vector<wstring>& properties) {
        IEnumWbemClassObject* pEnumerator = NULL;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            query,
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pEnumerator);

        if (FAILED(hres))
        {
            wcout << L"Query for " << query << L" failed. Error code = 0x"
                << hex << hres << endl;
            return;
        }

        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pEnumerator)
        {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
                &pclsObj, &uReturn);

            if (0 == uReturn)
            {
                break;
            }

            VARIANT vtProp;

            for (const auto& property : properties) {
                hr = pclsObj->Get(property.c_str(), 0, &vtProp, 0, 0);
                if (SUCCEEDED(hr)) {
                    switch (vtProp.vt) {
                    case VT_BSTR:
                        std::wcout << property << L" : " << vtProp.bstrVal << std::endl;
                        break;
                    case VT_I4:
                        std::wcout << property << L" : " << vtProp.intVal << std::endl;
                        break;
                    case VT_UI4:
                        std::wcout << property << L" : " << vtProp.uintVal << std::endl;
                        break;
                    case VT_BOOL:
                        std::wcout << property << L" : " << (vtProp.boolVal ? L"True" : L"False") << std::endl;
                        break;
                        // Add more cases as needed for other types
                    default:
                        std::wcout << property << L" : (Unknown type)" << std::endl;
                        break;
                    }
                }
                VariantClear(&vtProp);
            }

            pclsObj->Release();
        }

        pEnumerator->Release();
        };

    // Query different hardware information
    QueryWMIClass(_bstr_t(L"SELECT * FROM Win32_Processor"), { L"Name", L"Manufacturer", L"NumberOfCores", L"NumberOfLogicalProcessors" });
    QueryWMIClass(_bstr_t(L"SELECT * FROM Win32_PhysicalMemory"), { L"Capacity", L"Speed", L"Manufacturer", L"SerialNumber" });
    QueryWMIClass(_bstr_t(L"SELECT * FROM Win32_DiskDrive"), { L"Model", L"Manufacturer", L"InterfaceType", L"Size" });
    QueryWMIClass(_bstr_t(L"SELECT * FROM Win32_NetworkAdapter WHERE NetEnabled = TRUE"), { L"Name", L"Manufacturer", L"MACAddress", L"Speed" });
    QueryWMIClass(_bstr_t(L"SELECT * FROM Win32_VideoController"), { L"Name", L"AdapterRAM", L"DriverVersion" });

    // Cleanup
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}
