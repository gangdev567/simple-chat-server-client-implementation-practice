// common/Message.h

#pragma once

#include <string>
#include <vector>

enum class MessageType {
    TEXT,
    FILE_REQUEST,
    FILE_RESPONSE,
    AUTH_REQUEST,
    AUTH_RESPONSE
};

struct Message {
    MessageType type;
    std::string sender;
    std::string content;
    std::vector<char> fileData; // 파일 전송 시 사용
};