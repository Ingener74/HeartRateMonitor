/*
 * IHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEGENERATOR_H_
#define IHEARTRATEGENERATOR_H_

#include <vector>
#include <boost/tuple/tuple.hpp>

#include "HeartBeatRateTypes.h"

namespace hrm {

typedef double HeartValue;

class IHeartRateGenerator {
public:
    virtual ~IHeartRateGenerator() {
    }

    virtual std::vector<boost::tuple<TimeStamp, HeartValue> > getHeartRate() = 0;

protected:
    IHeartRateGenerator() {
    }
};

}  // namespace hrm

#endif /* IHEARTRATEGENERATOR_H_ */
