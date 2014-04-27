/*
 * HeartBeatRateTypes.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pavel
 */

#include <heartrate/HeartBeatRateTypes.h>

namespace hrm {

/*
// !!! ВНИМАНИЕ !!! Для корректного измерения времени включите опцию -O2
// а для компилятора C++ 4.6.3 ещё необходимо добавить опцию -std=c++0x
#include <chrono>
#include <iostream>

class TimeMeasure {
public:
   TimeMeasure() {
      start();
   }
   void start() {
      m_start = now();
   }
   int elapsed_ms() const {
      return elapsed< std::chrono::milliseconds >();
   }
   int elapsed_mks() const {
      return elapsed< std::chrono::microseconds >();
   }

private:
   template< class D >
   int elapsed() const {
      return std::chrono::duration_cast< D >( now() - m_start ).count();
   }
   const std::chrono::system_clock::time_point now() const {
      return std::chrono::system_clock::now();
   }
   std::chrono::system_clock::time_point m_start;
};

template< class F >
void measure_ms( const char * const text, F f ) {
   TimeMeasure m;
   f();
   int t = m.elapsed_ms();
   std::cout << text << " : " << t << " ms." << std::endl;
}

template< class F >
void measure_mks( const char * const text, F f ) {
   TimeMeasure m;
   f();
   int t = m.elapsed_mks();
   std::cout << text << " : " << t << " mks." << std::endl;
}
*/


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

