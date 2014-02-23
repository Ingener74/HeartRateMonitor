/*
 * RGBHeartRateGenerator.cpp
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#include "HeartRateTools.h"
#include "RGBHeartRateGenerator.h"

namespace hrm {

RGBHeartRateGenerator::RGBHeartRateGenerator(
        boost::shared_ptr<RGBFrameSource> rgbFrameSource,
        boost::shared_ptr<IImageDrawer> debugImageDrawer) :
            _rgbfs(rgbFrameSource), _did(debugImageDrawer){
}

RGBHeartRateGenerator::~RGBHeartRateGenerator() {
}

RawMeasurementGraph RGBHeartRateGenerator::getHeartRate() {

    {
        SharedLockedFrame slf = _rgbfs->getFrame();
        _did->drawImage(slf.get<1>());
    }

    RawMeasurementGraph rmg;
    rmg.push_back(RawMeasurement(1.0, 1.0));
    return rmg;
}

}  // namespace hrm

