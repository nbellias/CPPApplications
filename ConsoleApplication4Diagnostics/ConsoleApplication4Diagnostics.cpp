// ConsoleApplication4Diagnostics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <winbase.h>
#include <string>
#include <vector>

void CheckMemory() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    std::cout << "Memory in use: " << statex.dwMemoryLoad << "%\n";
    std::cout << "Total physical memory: " << statex.ullTotalPhys / 1024 / 1024 << " MB\n";
    std::cout << "Available physical memory: " << statex.ullAvailPhys / 1024 / 1024 << " MB\n";
}

void CheckCPUUsage() {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;
    PDH_FMT_COUNTERVALUE counterVal;

    PdhOpenQuery(NULL, NULL, &cpuQuery);
    PdhAddCounter(cpuQuery, TEXT("\\Processor(_Total)\\% Processor Time"), NULL, &cpuTotal);
    PdhCollectQueryData(cpuQuery);

    Sleep(1000);

    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    std::cout << "CPU Usage: " << counterVal.doubleValue << "%\n";

    PdhCloseQuery(cpuQuery);
}

void CheckDiskUsage() {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

    if (GetDiskFreeSpaceEx(L"C:\\", &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        std::cout << "Total space: " << totalNumberOfBytes.QuadPart / 1024 / 1024 / 1024 << " GB\n";
        std::cout << "Free space: " << totalNumberOfFreeBytes.QuadPart / 1024 / 1024 / 1024 << " GB\n";
    }
    else {
        std::cerr << "Error getting disk space: " << GetLastError() << "\n";
    }
}

void ReadEventLog() {
    HANDLE hEventLog = OpenEventLog(NULL, L"System");
    if (hEventLog == NULL) {
        std::cerr << "Could not open event log: " << GetLastError() << "\n";
        return;
    }

    const DWORD BUFFER_SIZE = 4096;
    BYTE buffer[BUFFER_SIZE];
    DWORD bytesRead = 0;
    DWORD minBytesNeeded = 0;

    if (!ReadEventLog(hEventLog, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ,
        0, buffer, BUFFER_SIZE, &bytesRead, &minBytesNeeded)) {
        std::cerr << "Could not read event log: " << GetLastError() << "\n";
        CloseEventLog(hEventLog);
        return;
    }

    EVENTLOGRECORD* record = (EVENTLOGRECORD*)buffer;
    while ((BYTE*)record < buffer + bytesRead) {
        std::wcout << L"Event ID: " << record->EventID << L", Source: " << (LPWSTR)((LPBYTE)record + sizeof(EVENTLOGRECORD)) << L"\n";
        record = (EVENTLOGRECORD*)((LPBYTE)record + record->Length);
    }

    CloseEventLog(hEventLog);
}


int main()
{
    std::cout << "Windows Diagnostics\n\n";

    std::cout << "Memory Check:\n";
    CheckMemory();
    std::cout << "\n";

    std::cout << "CPU Usage:\n";
    CheckCPUUsage();
    std::cout << "\n";

    std::cout << "Disk Usage:\n";
    CheckDiskUsage();
    std::cout << "\n";

    std::cout << "Event Log Reading:\n";
    ReadEventLog();
    std::cout << "\n";

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
