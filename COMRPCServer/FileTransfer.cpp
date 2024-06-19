// FileTransfer.cpp : Implementation of CFileTransfer

#include "pch.h"
#include "FileTransfer.h"
#include <fstream>
#include <atlcomcli.h>


// CFileTransfer

STDMETHODIMP CFileTransfer::SendFile(BSTR filePath)
{
    USES_CONVERSION;
    const char* szFilePath = OLE2A(filePath);
    std::ifstream file(szFilePath, std::ios::binary);

    if (!file.is_open())
    {
        return E_FAIL;
    }

    // Read the file and send its contents
    // This is a placeholder for actual file transfer logic

    file.close();
    return S_OK;
}

STDMETHODIMP CFileTransfer::ReceiveFile(BSTR filePath)
{
    USES_CONVERSION;
    const char* szFilePath = OLE2A(filePath);
    std::ofstream file(szFilePath, std::ios::binary);

    if (!file.is_open())
    {
        return E_FAIL;
    }

    // Receive the file and write its contents
    // This is a placeholder for actual file receiving logic

    file.close();
    return S_OK;
}