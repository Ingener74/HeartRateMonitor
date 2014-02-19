/*
 * SimpleHeartRateGenerator.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include "SimpleHeartRateGenerator.h"

namespace hrm {

SimpleHeartRateGenerator::SimpleHeartRateGenerator() {
}

SimpleHeartRateGenerator::~SimpleHeartRateGenerator() {
}

std::vector<boost::tuple<TimeStamp, HeartValue> >
    SimpleHeartRateGenerator::getHeartRate() {
    std::vector<boost::tuple<TimeStamp, HeartValue> > heartRateRawGraph;
    for (int i = 0; i < 60; ++i) {
        heartRateRawGraph.push_back(boost::tuple<TimeStamp, HeartValue>(i * 1.0, i * 0.2));
    }
    return heartRateRawGraph;
}

}  // namespace hrm
