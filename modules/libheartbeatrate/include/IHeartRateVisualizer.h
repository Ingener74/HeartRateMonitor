/*
 * IHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEVISUALIZER_H_
#define IHEARTRATEVISUALIZER_H_

#include <memory>

#include "HeartBeatRateTypes.h"

namespace hrm {

class IHeartRateVisualizer {
public:
	typedef std::shared_ptr<IHeartRateVisualizer> Ptr;

	virtual ~IHeartRateVisualizer() {
	}

	virtual void visualizeHeartRate(
			MeasurementGraph heartRateMeasuredGraph) = 0;

protected:
	IHeartRateVisualizer() {
	}
};

}  // namespace hrm

#endif /* IHEARTRATEVISUALIZER_H_ */
