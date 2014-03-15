/*
 * IHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEGENERATOR_H_
#define IHEARTRATEGENERATOR_H_

#include <memory>
#include <vector>

#include "HeartBeatRateTypes.h"

namespace hrm {

typedef double HeartValue;

class IHeartRateGenerator {
public:
	typedef std::shared_ptr<IHeartRateGenerator> Ptr;

	virtual ~IHeartRateGenerator() {
	}

	virtual RawMeasurementGraph getHeartRate() = 0;

protected:
	IHeartRateGenerator() {
	}
};

}  // namespace hrm

#endif /* IHEARTRATEGENERATOR_H_ */
