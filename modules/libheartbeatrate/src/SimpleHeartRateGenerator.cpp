/*
 * SimpleHeartRateGenerator.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include "unistd.h"

#include "SimpleHeartRateGenerator.h"

namespace hrm {

SimpleHeartRateGenerator::SimpleHeartRateGenerator() {
}

SimpleHeartRateGenerator::~SimpleHeartRateGenerator() {
}

RawMeasurementGraph SimpleHeartRateGenerator::getHeartRate() {

    usleep(30 * 1000); /* artificial delay */

    RawMeasurementGraph heartRateRawGraph;
    for (int i = 0; i < 60; ++i) {
        heartRateRawGraph.push_back(RawMeasurement(i * 1.0, i * 0.2));
    }
    return heartRateRawGraph;
}

}  // namespace hrm
