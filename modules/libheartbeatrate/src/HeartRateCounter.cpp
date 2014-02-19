/*
 * HeartRateCounter.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include "HeartRateCounter.h"

namespace hrm {

HeartRateCounter::HeartRateCounter(
        boost::shared_ptr<IHeartRateGenerator> hrGenerator,
        boost::shared_ptr<IHeartRateNumber> hrNumber,
        boost::shared_ptr<IHeartRateVisualizer> hrVisualizer) {
}

HeartRateCounter::~HeartRateCounter() {
}

bool HeartRateCounter::start() {
    return false;
}

void HeartRateCounter::stop() {
}

}  // namespace hrm

