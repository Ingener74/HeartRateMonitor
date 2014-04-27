/*
 * MockHeartRateRecognizer.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: ingener
 */

#include <heartrate/mocks/MockHeartRateRecognizer.h>

namespace hrm {
namespace mock {

MockHeartRateRecognizer::MockHeartRateRecognizer() {
}

MockHeartRateRecognizer::~MockHeartRateRecognizer() {
}

HrmHeartRate hrm::mock::MockHeartRateRecognizer::recognizeHeartRateValue(
        HrmMeasurement rawMeas) throw (HRRecognitionException)
{
    return {HrmHeartRate::State::Valid, 80};
}

} /* namespace mock */
} /* namespace hrm */

