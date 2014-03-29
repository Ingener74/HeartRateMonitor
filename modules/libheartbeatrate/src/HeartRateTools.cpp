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

HeartRateTools* HeartRateTools::instance() {
    static boost::shared_ptr<HeartRateTools> self(new HeartRateTools());
    return self.get();
}

HeartRateTools::~HeartRateTools() {
}

ILog* HeartRateTools::getLog() {
    return _log.get();
}

HeartRateTools::HeartRateTools() {
#ifdef ANDROID
#warning AndroidLog
    _log = boost::shared_ptr<ILog>(new AndroidLog());
#else
#warning LinuxLog
    _log = boost::shared_ptr<ILog>(new LinuxLog());
#endif
}

}  // namespace hrm

