/*
 * RGBHeartRateGenerator.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#ifndef RGBHEARTRATEGENERATOR_H_
#define RGBHEARTRATEGENERATOR_H_

#include <heartrate/IRGBFrameSource.h>
#include <heartrate/IRGBFrameDrawer.h>
#include <heartrate/IHeartRateGenerator.h>

namespace hrm {

class RGBHeartRateGenerator: public IHeartRateGenerator {
public:
    RGBHeartRateGenerator(
            IRGBFrameSource::Ptr rgbFrameSource,
            IRGBFrameDrawer::Ptr rgbFrameDrawer);
    virtual ~RGBHeartRateGenerator();

    virtual HrmMeasurement getHeartMeasurementValue()
                throw (HRGenerateException);

private:
    IRGBFrameSource::Ptr _rgbfs;
    IRGBFrameDrawer::Ptr _rgbfd;
};

}  // namespace hrm

#endif /* RGBHEARTRATEGENERATOR_H_ */
