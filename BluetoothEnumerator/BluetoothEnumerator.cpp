// BluetoothEnumerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <bthsdpdef.h>
#include <bluetoothapis.h>

#pragma comment(lib, "Bthprops.lib")

int main() {
    // Initialize Bluetooth find radio params
    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams;
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnUnknown = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fIssueInquiry = TRUE;
    searchParams.cTimeoutMultiplier = 1;
    searchParams.hRadio = nullptr;

    // Initialize device info struct
    BLUETOOTH_DEVICE_INFO deviceInfo;
    deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    HBLUETOOTH_DEVICE_FIND hDeviceFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);

    if (hDeviceFind == nullptr) {
        std::cout << "No Bluetooth devices found or an error occurred." << std::endl;
        return 1;
    }

    do {
        std::wcout << L"Device Name: " << deviceInfo.szName << std::endl;
        std::wcout << L"Device Address: "
            << deviceInfo.Address.ullLong << std::endl;

        std::wcout << L"Authenticated: " << (deviceInfo.fAuthenticated ? L"Yes" : L"No") << std::endl;
        std::wcout << L"Connected: " << (deviceInfo.fConnected ? L"Yes" : L"No") << std::endl;
        std::wcout << L"Remembered: " << (deviceInfo.fRemembered ? L"Yes" : L"No") << std::endl;
        std::wcout << L"----------------------------------" << std::endl;

    } while (BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

    BluetoothFindDeviceClose(hDeviceFind);

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
