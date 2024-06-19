#include "pch.h"
#include "Login.h"
#include <windows.h>
#include <lm.h> // For NetUserGetInfo and related functions

// Link with the necessary netapi libraries
#pragma comment(lib, "netapi32.lib")

bool ValidateCredentials(const char* username, const char* password) {
    HANDLE hToken;
    BOOL result = LogonUserA(
        username,           // Username
        ".",                // Use local computer
        password,           // User's password
        LOGON32_LOGON_INTERACTIVE, // Logon type
        LOGON32_PROVIDER_DEFAULT,  // Logon provider
        &hToken);           // Handle to the token

    if (result) {
        CloseHandle(hToken);
        return true;
    }
    else {
        return false;
    }
}

