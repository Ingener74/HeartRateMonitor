/*
 * IHeartRateRecognizer.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef IHEARTRATERECOGNIZER_H_
#define IHEARTRATERECOGNIZER_H_

#include <heartrate/types/Exception.h>
#include <heartrate/HeartRateCommon.h>
#include <heartrate/HeartBeatRateTypes.h>

namespace hrm {

class IHeartRateRecognizer {
public:
    typedef shared_ptr<IHeartRateRecognizer> Ptr;

    virtual ~IHeartRateRecognizer() {
    }

    virtual HeartRateValue recognizeHeartRateValue(
            RawMeasurementGraph rawMeasGraph) throw (HRRecognitionException) = 0;
protected:
    IHeartRateRecognizer() {
    }
};

}  // namespace hrm

#endif /* IHEARTRATERECOGNIZER_H_ */
