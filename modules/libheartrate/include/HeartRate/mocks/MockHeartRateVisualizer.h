/*
 * MockHeartRateVisualizer.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATEVISUALIZER_H_
#define MOCKHEARTRATEVISUALIZER_H_

#include <heartrate/IHeartRateVisualizer.h>

namespace hrm {
namespace mock {

class MockHeartRateVisualizer: public IHeartRateVisualizer {
public:
    MockHeartRateVisualizer();
    virtual ~MockHeartRateVisualizer();

    virtual void visualizeHeartRate(HrmMeasurementGraph heartRateMeasuredGraph)
                throw (HRVisualizeException);
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATEVISUALIZER_H_ */
