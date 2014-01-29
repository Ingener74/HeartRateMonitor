/*
 * HeartBeatRateTypes.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pavel
 */

#include <time.h>

#include "HeartBeatRateTypes.h"

namespace hrm {

TimeCounter* TimeCounter::instance() {
    static boost::scoped_ptr<TimeCounter> self(new TimeCounter());
    return self.get();
}

TimeCounter::TimeCounter() :
        _time(0.0){
}
TimeCounter::~TimeCounter() {
}

TimeStamp TimeCounter::getTimeStamp() {
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC, &tm);

    uint64_t t = tm.tv_sec * 1000000000LL + tm.tv_nsec;
    _time = t;
    return _time;
}

boost::tuple<TimeStamp, ElapsedTime> TimeCounter::getTimeStampExt() {
    TimeStamp time = getTimeStamp();
    ElapsedTime dt = time - _time;
    _time = time;
    return boost::tuple<TimeStamp, ElapsedTime>(time, dt);
}

}  // namespace hrm
