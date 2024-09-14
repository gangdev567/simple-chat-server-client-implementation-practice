#include "Server.h"

#include <functional>
#include <iostream>
#include <sys/select.h>

Server::Server(int port) : m_serverSocket(-1) {
    // 서버 소켓 생성 및 설정
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&m_serverAddr, 0, sizeof(m_serverAddr));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.s_addr = INADDR_ANY;
    m_serverAddr.sin_port = htons(port);

    if(bind(m_serverSocket, (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(m_serverSocket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&m_masterFDSet);
    FD_SET(m_serverSocket, &m_masterFDSet);
}

Server::~Server() {
    close(m_serverSocket);
}

void Server::start() {
    while (true) {
        fd_set readFDSet = m_masterFDSet;
        if (select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL) < 0) {
            perror("select failed");
            continue;
        }

        if (FD_ISSET(m_serverSocket, &readFDSet)) {
            handleNewConnection();
        }

        // 기존 클라이언트들로부터 메시지 처리
        for (int i =0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &readFDSet) && i != m_serverSocket) {
                handleMessageFromClient(i);
            }
        }
    }
}

void Server::handleNewConnection() {
    int clientSocket = accept(m_serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        perror("accept failed");
        return;
    }

    FD_SET(clientSocket, &m_masterFDSet);

    // 클라이언트 인증 요청 전송
    Message authRequest;
    authRequest.type = MessageType::AUTH_REQUEST;
    send(cliendSocket, &authRequest, sizeof(Message), 0);

    std::cout << "New connection accepted." << std::endl;
}

void Server::handleMessageFromClient(int clientSocket) {
    Message message;
    ssize_t bytesReceived = recv(clientSocket, &message, sizeof(Message), 0);
    if (bytesReceived <= 0) {
        close(clientSocket);
        FD_CLR(clientSocket, &m_masterFDSet);
        std::cout << "Client disconnected." << std::endl;
        return;
    }

    switch (message.type) {
        case MessageType::AUTH_RESPONSE:
            // 인증 응답 처리
                break;
        case MessageType::TEXT:
            // 텍스트 메시지 처리 및 브로드캐스팅
                break;
        case MessageType::FILE_REQUEST:
            // 파일 요청 처리
                break;
        default:
            std::cerr << "Unknown message type received." << std::endl;
        break;
    }
}