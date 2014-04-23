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

HeartRateValue MockHeartRateRecognizer::recognizeHeartRateValue(
        RawMeasurementGraph rawMeasGraph) throw (HRRecognitionException) {

    return 80.0;
}

} /* namespace mock */
} /* namespace hrm */
