/*
 * AndroidLog.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <android/log.h>

#include "HeartBeatRateDefines.h"
#include "AndroidLog.h"

namespace hrm {

AndroidLog::AndroidLog() {
}

AndroidLog::~AndroidLog() {
}

void AndroidLog::DEBUG(const std::string& message) {
    __android_log_print(ANDROID_LOG_DEBUG, HRM_TAG, "%s", message.c_str());
}

void AndroidLog::INFO(const std::string& message) {
}

void AndroidLog::ERROR(const std::string& message) {
}

void AndroidLog::WARN(const std::string& message) {
}

}  // namespace hrm

