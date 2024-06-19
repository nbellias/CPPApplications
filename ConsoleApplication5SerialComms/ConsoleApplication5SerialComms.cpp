// ConsoleApplication5SerialComms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>

void ErrorHandler(const char* errorMsg) {
    std::cerr << "Error: " << errorMsg << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    // Open the serial port
    hSerial = CreateFile(
        L"\\\\.\\COM5",      // Specify the COM port name. Adjust as needed.
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        ErrorHandler("Opening serial port");
    }

    // Set device parameters (9600 baud, 1 start bit, 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        ErrorHandler("Getting current serial parameters");
    }

    dcbSerialParams.BaudRate = CBR_57600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        ErrorHandler("Setting serial parameters");
    }

    // Set COM port timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        ErrorHandler("Setting serial timeouts");
    }

    // Capture data from the serial port
    char szBuff[1024];
    DWORD dwBytesRead = 0;
    BOOL bResult = FALSE;

    std::cout << "Reading from COM port..." << std::endl;

    while (true) {
        bResult = ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL);
        if (!bResult) {
            ErrorHandler("Reading from serial port");
        }

        szBuff[dwBytesRead] = '\0';  // Null-terminate the buffer

        if (dwBytesRead > 0) {
            std::cout << szBuff;
        }
    }

    // Close the serial port
    CloseHandle(hSerial);
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
