/*
 * SimpleHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef SIMPLEHEARTRATEGENERATOR_H_
#define SIMPLEHEARTRATEGENERATOR_H_

#include "heartratemonitor/IHeartRateGenerator.h"

namespace hrm {

class SimpleHeartRateGenerator: public IHeartRateGenerator {
public:
    SimpleHeartRateGenerator();
    virtual ~SimpleHeartRateGenerator();

    virtual RawMeasurementGraph getHeartRate();
private:
};

}  // namespace hrm

#endif /* SIMPLEHEARTRATEGENERATOR_H_ */
