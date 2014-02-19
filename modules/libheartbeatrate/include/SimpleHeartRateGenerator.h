/*
 * SimpleHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef SIMPLEHEARTRATEGENERATOR_H_
#define SIMPLEHEARTRATEGENERATOR_H_

#include "IHeartRateGenerator.h"

namespace hrm {

class SimpleHeartRateGenerator: public IHeartRateGenerator {
public:
    SimpleHeartRateGenerator();
    virtual ~SimpleHeartRateGenerator();

    virtual std::vector<boost::tuple<TimeStamp, HeartValue> > getHeartRate();

private:
};

}  // namespace hrm

#endif /* SIMPLEHEARTRATEGENERATOR_H_ */
