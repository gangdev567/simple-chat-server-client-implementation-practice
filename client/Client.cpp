// client/Client.cpp
#include "Client.h"
#include <thread>
#include <iostream>

Client::Client(const std::string& serverIP, int port) : m_clientSocket(-1) {
    // 클라이언트 소켓 생성 및 설정
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_clientSocket < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&m_serverAddr, 0, sizeof(m_serverAddr));
    m_serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, sererIP.c_str(), &m_serverAddr.sin_addr);
    m_serverAddr.sin_port = htons(port);

    connectToServer();
}
Client::~Client() {
    close(m_clientSocket);
}

void Client::connectToServer() {
    if (connect(m_clientSocket ))
}