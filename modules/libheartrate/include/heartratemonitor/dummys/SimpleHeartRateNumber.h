/*
 * SimpleHeartRateNumber.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef SIMPLEHEARTRATENUMBER_H_
#define SIMPLEHEARTRATENUMBER_H_

#include <heartratemonitor/HeartRateTools.h>
#include <heartratemonitor/IHeartRateNumber.h>

namespace hrm {

class SimpleHeartRateNumber: public IHeartRateNumber {
public:
    SimpleHeartRateNumber() {
    }
    virtual ~SimpleHeartRateNumber() {
    }

    virtual void setHeartRateNumber(HeartRateValue heartRateNumber) {
        HeartRateTools::instance()->getLog()->INFO((
                format("Heart rate = %1% beats per minute") % heartRateNumber
                ).str());
    }

private:
};

}  // namespace hrm

#endif /* SIMPLEHEARTRATENUMBER_H_ */
