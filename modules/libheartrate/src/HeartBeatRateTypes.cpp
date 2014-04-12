/*
 * HeartBeatRateTypes.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pavel
 */

#include <heartrate/HeartBeatRateTypes.h>

namespace hrm {

TimeCounter* TimeCounter::instance() {
    static boost::scoped_ptr<TimeCounter> self(new TimeCounter());
    return self.get();
}

TimeCounter::TimeCounter() :
        _time(0.0) {
}
TimeCounter::~TimeCounter() {
}

TimeStamp TimeCounter::getTimeStamp() {
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC, &tm);

    _time = double(tm.tv_sec * 1000 + tm.tv_nsec / 1000000);
    return _time;
}

boost::tuple<TimeStamp, ElapsedTime> TimeCounter::getTimeStampExt() {
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC, &tm);
    TimeStamp time = TimeStamp(tm.tv_sec * 1000 + tm.tv_nsec / 1000000);
    ElapsedTime dt = time - _time;
    _time = time;
    return boost::tuple<TimeStamp, ElapsedTime>(time, dt);
}

}  // namespace hrm

