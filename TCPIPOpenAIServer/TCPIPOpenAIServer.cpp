#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "httplib.h" // Include cpp-httplib

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

#define PORT "8080"
#define BUFSIZE 1024

using namespace httplib;

const std::string OPENAI_API_KEY = "sk-proj-8RWeZvl1DnU7fd59CGH2T3BlbkFJpAqAYCKEgcNM7E3F4usp";
const std::string OPENAI_API_URL = "https://api.openai.com/v1/chat/completions";

// Function to query ChatGPT
std::string query_chatgpt(const std::string& question) {
    SSLClient cli("api.openai.com", 443);
    Headers headers = {
        { "Authorization", "Bearer " + OPENAI_API_KEY },
        { "Content-Type", "application/json" }
    };

    std::string body = 
        "{ \"model\": \"gpt-3.5-turbo\", \"messages\": [ { \"role\": \"system\", \"content\": \"You are a helpful assistant.\" }, { \"role\": \"user\", \"content\": \"" + question + "\" } ] }";

    auto res = cli.Post("/v1/chat/completions", headers, body, "application/json");

    if (res && res->status == 200) {
        auto result = res->body.find("\"text\":");
        if (result != std::string::npos) {
            std::string response = res->body.substr(result + 8);
            return response;
        }
    }
    return "Error: Could not get response from ChatGPT.";
}

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
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, PORT, &hints, &addr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }

    result = bind(listenSocket, addr->ai_addr, (int)addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addr);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(addr);

    result = listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    SOCKET clientSocket = INVALID_SOCKET;

    while (true) {
        clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        char recvbuf[BUFSIZE];
        int recvbuflen = BUFSIZE;

        result = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (result > 0) {
            recvbuf[result] = '\0';
            std::string question(recvbuf);
            std::cout << "Received question: " << question << std::endl;

            std::string response = query_chatgpt(question);

            result = send(clientSocket, response.c_str(), response.length(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "send failed: " << WSAGetLastError() << std::endl;
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }
        }
        else if (result == 0) {
            std::cout << "Connection closing..." << std::endl;
        }
        else {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        closesocket(clientSocket);
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
