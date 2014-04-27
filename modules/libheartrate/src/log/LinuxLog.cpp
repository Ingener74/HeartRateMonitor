/*
 * LinuxLog.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <iostream>
#include "LinuxLog.h"

namespace hrm {

LinuxLog::LinuxLog() {
}

LinuxLog::~LinuxLog() {
}

void LinuxLog::DEBUG(const std::string& message) {
    std::cout << message << std::endl;
}

void LinuxLog::INFO(const std::string& message) {
    std::cout << message << std::endl;
}

void LinuxLog::ERR(const std::string& message) {
    std::cout << message << std::endl;
}

void LinuxLog::WARN(const std::string& message) {
    std::cout << message << std::endl;
}

void LinuxLog::DEBUG(const basic_format<char>& messages) {
    std::cout << messages << std::endl;
}

void LinuxLog::INFO(const basic_format<char>& messages) {
    std::cout << messages << std::endl;
}

void LinuxLog::ERR(const basic_format<char>& messages) {
    std::cerr << messages << std::endl;
}

void LinuxLog::WARN(const basic_format<char>& messages) {
    std::cerr << messages << std::endl;
}

}  // namespace hrm

