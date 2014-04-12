/*
 * RGBHeartRateGenerator.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#ifndef RGBHEARTRATEGENERATOR_H_
#define RGBHEARTRATEGENERATOR_H_

#include "HeartBeatRateTypes.h"
#include "IRGBFrameSource.h"
#include "IHeartRateGenerator.h"
#include "IRGBFrameDrawer.h"

namespace hrm {

class RGBHeartRateGenerator: public IHeartRateGenerator {
public:
    RGBHeartRateGenerator(
            IRGBFrameSource::Ptr rgbFrameSource,
            IRGBFrameDrawer::Ptr rgbFrameDrawer);
    virtual ~RGBHeartRateGenerator();

    virtual RawMeasurementGraph getHeartRate();

private:
    IRGBFrameSource::Ptr _rgbfs;
    RawMeasurementGraph _rawGraph;

    IRGBFrameDrawer::Ptr _rgbfd;
};

}  // namespace hrm

#endif /* RGBHEARTRATEGENERATOR_H_ */