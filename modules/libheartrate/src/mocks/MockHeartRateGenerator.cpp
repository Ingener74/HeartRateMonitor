/*
 * MockHeartRateGenerator.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */


#include <heartrate/mocks/MockHeartRateGenerator.h>

namespace hrm {
namespace mock {

MockHeartRateGenerator::MockHeartRateGenerator() {
}

MockHeartRateGenerator::~MockHeartRateGenerator() {
}

RawMeasurementGraph MockHeartRateGenerator::getHeartRate() {

    this_thread::sleep(posix_time::milliseconds(30)); /* artificial delay */

    RawMeasurementGraph heartRateRawGraph;
    for (int i = 0; i < 60; ++i) {
        heartRateRawGraph.push_back(RawMeasurement(i * 1.0, i * 0.2));
    }
    return heartRateRawGraph;
}

} /* namespace mock */
} /* namespace hrm */
