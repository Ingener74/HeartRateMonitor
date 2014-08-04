/*
 * MockHeartRateGenerator.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATEGENERATOR_H_
#define MOCKHEARTRATEGENERATOR_H_

#include <heartrate/IHeartRateGenerator.h>

namespace hrm {
namespace mock {

class MockHeartRateGenerator: public IHeartRateGenerator {
public:
    MockHeartRateGenerator();
    virtual ~MockHeartRateGenerator();

    virtual HrmMeasurement getHeartMeasurementValue()
            throw (HRGenerateException);
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATEGENERATOR_H_ */
