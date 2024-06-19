// WindowsAPIFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>
#include <atlstr.h>

using namespace std;

void CreateNewProcess() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

	LPWSTR commandLine = CA2CT("notepad.exe");

    // Start the child process.
    if (!CreateProcess(
        NULL,                   // No module name (use command line)
        commandLine,   // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // No creation flags
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory 
        &si,                    // Pointer to STARTUPINFO structure
        &pi)                    // Pointer to PROCESS_INFORMATION structure
        ) {
        cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void CreateOrOpenFile() {
	LPCWSTR fileName = L"example.txt";
    HANDLE hFile = CreateFile(
        fileName,           // Name of the file
        GENERIC_WRITE,           // Open for writing
        0,                       // Do not share
        NULL,                    // Default security
        CREATE_ALWAYS,           // Always create a new file
        FILE_ATTRIBUTE_NORMAL,   // Normal file
        NULL);                   // No template file

    if (hFile == INVALID_HANDLE_VALUE) {
        cerr << "CreateFile failed (" << GetLastError() << ").\n";
        return;
    }

    // Write to the file
    const char* data = "Hello, World!";
    DWORD bytesWritten;
    BOOL result = WriteFile(
        hFile,          // Handle to the file
        data,           // Data to write
        strlen(data),   // Number of bytes to write
        &bytesWritten,  // Number of bytes that were written
        NULL);          // No overlapped structure

    if (!result) {
        cerr << "WriteFile failed (" << GetLastError() << ").\n";
    }
    else {
        cout << "Successfully wrote to the file.\n";
    }

    // Close the file handle
    CloseHandle(hFile);
}

void ProcessMessages() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main() {
    cout << "Creating a new process...\n";
    CreateNewProcess();

    cout << "Creating or opening a file...\n";
    CreateOrOpenFile();

    cout << "Processing messages...\n";
    ProcessMessages();

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
