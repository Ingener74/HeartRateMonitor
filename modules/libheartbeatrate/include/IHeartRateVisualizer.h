/*
 * IHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEVISUALIZER_H_
#define IHEARTRATEVISUALIZER_H_

#include <boost/shared_ptr.hpp>

#include "HeartBeatRateTypes.h"

namespace hrm {

class IHeartRateVisualizer {
public:
	typedef boost::shared_ptr<IHeartRateVisualizer> Ptr;

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
