// common/Utils.h
#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string& str);

template<typename T>
std::string serialize(T value) {
    std::stringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(sizeof(T)*2);
    oss << static_cast<int>(value);
    return oss.str();
}

template<typename T>
T deserialize(const std::string& hexString) {
    std::istringstream iss(hexString);
    T value;
    iss >> std::hex >> value;
    return value;
}