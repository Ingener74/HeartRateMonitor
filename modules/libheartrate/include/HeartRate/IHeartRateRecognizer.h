/*
 * IHeartRateRecognizer.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef IHEARTRATERECOGNIZER_H_
#define IHEARTRATERECOGNIZER_H_

#include <heartrate/types/Exception.h>
#include <heartrate/types/Types.h>
#include <heartrate/HeartRateCommon.h>

namespace hrm
{

class IHeartRateRecognizer
{
public:
    using Ptr = shared_ptr<IHeartRateRecognizer>;

    virtual ~IHeartRateRecognizer()
    {
    }

    virtual HrmHeartRate recognizeHeartRateValue(HrmMeasurement rawMeas)
            throw (HRRecognitionException) = 0;
protected:
    IHeartRateRecognizer()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATERECOGNIZER_H_ */
