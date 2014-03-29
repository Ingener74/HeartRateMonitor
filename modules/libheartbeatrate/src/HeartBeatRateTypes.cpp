/*
 * HeartBeatRateTypes.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pavel
 */

#include <time.h>
#include <algorithm>

#include "heartratemonitor/HeartBeatRateTypes.h"

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

//void Image::drawLine(Image image, const Point& p1,
//        const Point& p2,
//        const Color& color,
//        DrawLineMethod method) {
//    if(image.getFormat()._bitsPerPixel != 24){
//        return;
//    }
//    switch (method) {
//    case DrawLineMethod_DDA: {
//        uint8_t* data = image.getData();
//        ImageRect ir = image.getFormat()._rect;
//        int L = std::max(std::abs(p2.x - p1.x), std::abs(p2.y - p1.y));
//
//        double dX = (p2.x - p1.x) / L,
//                dY = (p2.y - p1.y) / L;
//
//        int x = p1.x, y = p1.y;
//
//        *(data + y*(ir._cols * 3) + x + 0) = color.r;
//        *(data + y*(ir._cols * 3) + x + 1) = color.g;
//        *(data + y*(ir._cols * 3) + x + 2) = color.b;
//
//        for (int i = 1, imax = L; i < imax; ++i) {
//            x += dX;
//            y += dY;
//
//            *(data + y*ir._cols + x + 0) = color.r;
//            *(data + y*ir._cols + x + 1) = color.g;
//            *(data + y*ir._cols + x + 2) = color.b;
//        }
//        break;
//    }
//    case DrawLineMethod_Bresenham: {
//        break;
//    }
//    case DrawLineMethod_By: {
//        break;
//    }
//    default:
//        break;
//    }
//}

}  // namespace hrm

