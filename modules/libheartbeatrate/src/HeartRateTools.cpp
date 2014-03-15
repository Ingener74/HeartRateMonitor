/*
 * HeartRateTools.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <memory>

#ifdef ANDROID
#include "AndroidLog.h"
#else
#include "LinuxLog.h"
#endif

#include "HeartRateTools.h"

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
    _log = std::shared_ptr<ILog>(new AndroidLog());
#else
#warning LinuxLog
    _log = std::shared_ptr<ILog>(new LinuxLog());
#endif
}

}  // namespace hrm

