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

}  // namespace hrm

