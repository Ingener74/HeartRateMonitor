/*
 * IHeartRateNumber.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATENUMBER_H_
#define IHEARTRATENUMBER_H_

#include <stdint.h>

namespace hrm {

class IHeartRateNumber {
public:
    virtual ~IHeartRateNumber() {
    }

    virtual void setHeartRateNumber(int32_t heartRateNumber) = 0;

protected:
    IHeartRateNumber() {
    }
};

}  // namespace hrm

#endif /* IHEARTRATENUMBER_H_ */
