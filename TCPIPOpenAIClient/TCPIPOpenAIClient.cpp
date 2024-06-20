#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT "8080"
#define SERVER "127.0.0.1"
#define BUFSIZE 1024

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    struct addrinfo* addr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(SERVER, PORT, &hints, &addr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKET connectSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }

    result = connect(connectSocket, addr->ai_addr, (int)addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(addr);

    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    int recvbuflen = BUFSIZE;

    std::cout << "Enter a question: ";
    std::cin.getline(sendbuf, BUFSIZE);

    result = send(connectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    result = recv(connectSocket, recvbuf, recvbuflen, 0);
    if (result > 0) {
        recvbuf[result] = '\0';
        std::cout << "Answer from server: " << recvbuf << std::endl;
    }
    else if (result == 0) {
        std::cout << "Connection closed" << std::endl;
    }
    else {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }

    closesocket(connectSocket);
    WSACleanup();
    return 0;
}
