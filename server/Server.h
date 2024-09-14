// server/Server.h
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "../common/Message.h"

class Server {
public:
    Server(int port);
    ~Server();

    void start();
private:
    int m_serverSocket;
    struct sockaddr_in m_serverAddr;
    fd_set m_masterFDSet;

    std::map<int, std::string> m_clientMap;

    void handleNewConnection();
    void handleMessageFromClient(int clientSocket);
};