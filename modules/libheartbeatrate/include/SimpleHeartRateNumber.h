/*
 * SimpleHeartRateNumber.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef SIMPLEHEARTRATENUMBER_H_
#define SIMPLEHEARTRATENUMBER_H_

#include "IHeartRateNumber.h"

namespace hrm {

class SimpleHeartRateNumber: public IHeartRateNumber{
public:
    SimpleHeartRateNumber() {
    }
    virtual ~SimpleHeartRateNumber() {
    }

    virtual void setHeartRateNumber(int32_t heartRateNumber){
    }

private:
};

}  // namespace hrm

#endif /* SIMPLEHEARTRATENUMBER_H_ */
