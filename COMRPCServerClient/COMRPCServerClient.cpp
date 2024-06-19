// COMRPCServerClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <atlbase.h>
#include "../COMRPCServer/COMRPCServer_i.h"


int main()
{
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::wcout << L"Failed to initialize COM library. Error code: " << hr << std::endl;
        return 1;
    }

    CComPtr<IFileTransfer> spFileTransfer;
    hr = spFileTransfer.CoCreateInstance(__uuidof(FileTransfer));
    if (FAILED(hr)) {
        std::wcout << L"Failed to create FileTransfer instance. Error code: " << hr << std::endl;
        CoUninitialize();
        return 1;
    }

    hr = spFileTransfer->SendFile(CComBSTR(L"C:\\Users\\nibe\\SEND\\nikos.txt"));
    if (SUCCEEDED(hr)) {
        std::wcout << L"File sent successfully." << std::endl;
    }
    else {
        std::wcout << L"Failed to send file. Error code: " << hr << std::endl;
    }

    hr = spFileTransfer->ReceiveFile(CComBSTR(L"C:\\Users\\nibe\\RECEIVE\\nikos.txt"));
    if (SUCCEEDED(hr)) {
        std::wcout << L"File received successfully." << std::endl;
    }
    else {
        std::wcout << L"Failed to receive file. Error code: " << hr << std::endl;
    }

    CoUninitialize();
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
