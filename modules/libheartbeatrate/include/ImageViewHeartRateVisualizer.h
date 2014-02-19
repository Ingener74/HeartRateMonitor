/*
 * ImageViewHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IMAGEVIEWHEARTRATEVISUALIZER_H_
#define IMAGEVIEWHEARTRATEVISUALIZER_H_

#include <jni.h>

#include "IHeartRateVisualizer.h"

namespace hrm {

class ImageViewHeartRateVisualizer: public IHeartRateVisualizer {
public:
    ImageViewHeartRateVisualizer();
    virtual ~ImageViewHeartRateVisualizer();

    virtual void visualizeHeartRate(MeasurementGraph heartRateMeasuredGraph);

private:
};

}  // namespace hrm

#endif /* IMAGEVIEWHEARTRATEVISUALIZER_H_ */
