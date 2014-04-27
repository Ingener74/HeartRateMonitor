/*
 * MockHeartRateRecognizer.h
 *
 *  Created on: Apr 19, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATERECOGNIZER_H_
#define MOCKHEARTRATERECOGNIZER_H_

#include <heartrate/IHeartRateRecognizer.h>

namespace hrm
{
namespace mock
{

class MockHeartRateRecognizer: public IHeartRateRecognizer
{
public:
    MockHeartRateRecognizer();
    virtual ~MockHeartRateRecognizer();

    virtual HrmHeartRate recognizeHeartRateValue(HrmMeasurement rawMeas)
            throw (HRRecognitionException);
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATERECOGNIZER_H_ */
