/*
 * HeartRateTools.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifdef ANDROID
#include "log/AndroidLog.h"
#else
#include "log/LinuxLog.h"
#endif

#include <heartrate/HeartRateTools.h>

namespace hrm {

HeartRateTools::Ptr HeartRateTools::instance() {
    static HeartRateTools::Ptr self(new HeartRateTools());
    return self;
}

HeartRateTools::~HeartRateTools() {
}

void hrm::HeartRateTools::setLog(ILog::Ptr log) {
    _log = log;
}

ILog::Ptr HeartRateTools::getLog() {
    return _log;
}

int32_t HeartRateTools::rountUpToNextPowerOfTwo(int32_t x) {
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

HeartRateTools::HeartRateTools() {
#ifdef ANDROID
    _log = ILog::Ptr(new AndroidLog());
#else
    _log = ILog::Ptr(new LinuxLog());
#endif
}

}  // namespace hrm

