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

#include "heartratemonitor/HeartRateTools.h"

namespace hrm {

boost::shared_ptr<HeartRateTools> HeartRateTools::instance() {
    static boost::shared_ptr<HeartRateTools> self(new HeartRateTools());
    return self;
}

HeartRateTools::~HeartRateTools() {
}

ILog::Ptr HeartRateTools::getLog() {
    return _log;
}

HeartRateTools::HeartRateTools() {
#ifdef ANDROID
    _log = ILog::Ptr(new AndroidLog());
#else
    _log = ILog::Ptr(new LinuxLog());
#endif
}

}  // namespace hrm

