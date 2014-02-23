/*
 * RGBHeartRateGenerator.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#ifndef RGBHEARTRATEGENERATOR_H_
#define RGBHEARTRATEGENERATOR_H_

#include <boost/smart_ptr.hpp>

#include "RGBFrameSource.h"
#include "IImageDrawer.h"
#include "IHeartRateGenerator.h"

namespace hrm {

class RGBHeartRateGenerator: public IHeartRateGenerator {
public:
    RGBHeartRateGenerator(
            boost::shared_ptr<RGBFrameSource> rgbFrameSource,
            boost::shared_ptr<IImageDrawer> debugImageDrawer);
    virtual ~RGBHeartRateGenerator();

    virtual RawMeasurementGraph getHeartRate();

private:
    boost::shared_ptr<RGBFrameSource> _rgbfs;
    boost::shared_ptr<IImageDrawer> _did;
};

}  // namespace hrm

#endif /* RGBHEARTRATEGENERATOR_H_ */
