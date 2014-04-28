/*
 * MockHeartRateNumber.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATENUMBER_H_
#define MOCKHEARTRATENUMBER_H_

#include <heartrate/IHeartRateNumber.h>
#include <heartrate/Log.h>

namespace hrm {
namespace mock {

class MockHeartRateNumber: public IHeartRateNumber {
public:
    MockHeartRateNumber(){
    }
    virtual ~MockHeartRateNumber(){}

    virtual void setHeartRate(HrmHeartRate heartRate)
            throw (HRNumberException){
        Log(INFO) << format("Heart rate = %1% beats per minute") %
                heartRate.value;
    }
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATENUMBER_H_ */
