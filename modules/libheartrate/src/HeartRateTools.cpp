/*
 * HeartRateTools.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <HeartRate/HeartRateTools.h>

namespace hrm {

HeartRateTools::Ptr HeartRateTools::instance() {
    static HeartRateTools::Ptr self(new HeartRateTools());
    return self;
}

HeartRateTools::~HeartRateTools() {
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

}  // namespace hrm

