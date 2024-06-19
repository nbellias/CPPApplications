#include <iostream>
#include <Windows.h>
#include <Dbt.h>
#include <initguid.h>
#include <devguid.h>
#include <usbiodef.h>
#include <Ntddkbd.h>
#include <Ntddmou.h>
#include <SetupAPI.h>
#include <winioctl.h>

using namespace std;

#pragma comment(lib, "setupapi.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CheckDeviceType(const GUID& interfaceClassGuid) {
    cout << "interfaceClassGuid = " << interfaceClassGuid.Data1 << "-" << interfaceClassGuid.Data2 << "-" << interfaceClassGuid.Data3 << "-" << interfaceClassGuid.Data4 << endl;
    if (interfaceClassGuid == GUID_DEVINTERFACE_MOUSE) {
        cout << "Mouse connected!" << endl;
    }
    else if (interfaceClassGuid == GUID_DEVINTERFACE_KEYBOARD) {
        cout << "Keyboard connected!" << endl;
    }
    else if (interfaceClassGuid == GUID_DEVINTERFACE_DISK) {
        cout << "Flash drive connected!" << endl;
    }
    else {
        cout << "Other device connected!" << endl;
    }
}

int main() {
    // Create a simple window class and window
    const char* CLASS_NAME = "USBListener";
    WNDCLASSA wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "USB Device Listener",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        cerr << "Failed to create window!" << endl;
        return 0;
    }

    ShowWindow(hwnd, SW_HIDE); // Hide the window

    // Register for device notifications
    DEV_BROADCAST_DEVICEINTERFACE notificationFilter = { };
    notificationFilter.dbcc_size = sizeof(notificationFilter);
    notificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    notificationFilter.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
    HDEVNOTIFY hDeviceNotify = RegisterDeviceNotification(hwnd, &notificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);

    if (!hDeviceNotify) {
        cerr << "Failed to register device notification!" << endl;
        return 0;
    }

    // Run the message loop
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterDeviceNotification(hDeviceNotify);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DEVICECHANGE:
        if (wParam == DBT_DEVICEARRIVAL) {
            cout << "Device connected!" << endl;
            PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
            if (pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                PDEV_BROADCAST_DEVICEINTERFACE pInterface = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
                cout << "Device name = " << pInterface->dbcc_name << endl;
                cout << "Device type = " << pInterface->dbcc_devicetype << endl;
                CheckDeviceType(pInterface->dbcc_classguid);
            }
        }
        else if (wParam == DBT_DEVICEREMOVECOMPLETE) {
            cout << "Device disconnected!" << endl;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
