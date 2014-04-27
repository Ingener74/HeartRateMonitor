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

HrmMeasurement MockHeartRateGenerator::getHeartMeasurementValue()
        throw (HRGenerateException)
{
    this_thread::sleep(posix_time::milliseconds(30)); /* artificial delay */

    return {0.0, 0.0};
}

} /* namespace mock */
} /* namespace hrm */

