/*
 * SimpleHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef SIMPLEHEARTRATEVISUALIZER_H_
#define SIMPLEHEARTRATEVISUALIZER_H_

#include "heartratemonitor/IHeartRateVisualizer.h"

namespace hrm {

class SimpleHeartRateVisualizer: public IHeartRateVisualizer {
public:
    SimpleHeartRateVisualizer();
    virtual ~SimpleHeartRateVisualizer();

    virtual void visualizeHeartRate(MeasurementGraph heartRateMeasuredGraph);

private:
};

}  // namespace hrm

#endif /* SIMPLEHEARTRATEVISUALIZER_H_ */
