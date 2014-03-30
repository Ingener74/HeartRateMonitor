/*
 * RGBHeartRateGenerator.h
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#ifndef RGBHEARTRATEGENERATOR_H_
#define RGBHEARTRATEGENERATOR_H_

#include <boost/smart_ptr.hpp>

#include "IRGBFrameSource.h"
#include "IRGBImageDrawer.h"
#include "IHeartRateGenerator.h"

namespace hrm {

class RGBHeartRateGenerator: public IHeartRateGenerator {
public:
    RGBHeartRateGenerator(
            IRGBFrameSource::Ptr rgbFrameSource/*,
            IRGBImageDrawer::Ptr debugImageDrawer*/);
    virtual ~RGBHeartRateGenerator();

    virtual RawMeasurementGraph getHeartRate();

private:
    IRGBFrameSource::Ptr _rgbfs;
//    IRGBImageDrawer::Ptr _did;

    RawMeasurementGraph _rawGraph;
};

}  // namespace hrm

#endif /* RGBHEARTRATEGENERATOR_H_ */
