/*
 * MockHeartRateNumber.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATENUMBER_H_
#define MOCKHEARTRATENUMBER_H_

#include <heartrate/IHeartRateNumber.h>

namespace hrm {
namespace mock {

class MockHeartRateNumber: public IHeartRateNumber {
public:
    MockHeartRateNumber(){
        HRM_DEBUG("MockHeartRateNumber()");
    }
    virtual ~MockHeartRateNumber(){}

    virtual void setHeartRate(HrmHeartRate heartRate)
            throw (HRNumberException){
        HRM_INFO((
                format("Heart rate = %1% beats per minute") % heartRate.value
                ).str());
    }
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATENUMBER_H_ */
