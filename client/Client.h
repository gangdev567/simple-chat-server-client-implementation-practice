// client/Client.h
#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../common/Message.h"

class Client {
public:
    Client(const std::string& serverIP, int port);
    ~Client();

    void start();
private:
    int m_clientSocket;
    struct sockaddr_in m_serverAddr;

    void connectToServer();
    void handleServerMessages();
    void handleUserInput();
};