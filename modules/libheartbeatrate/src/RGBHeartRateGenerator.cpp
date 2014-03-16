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
        IRGBFrameSource::Ptr rgbFrameSource,
        IRGBImageDrawer::Ptr debugImageDrawer) :
            _rgbfs(rgbFrameSource), _did(debugImageDrawer){
}

RGBHeartRateGenerator::~RGBHeartRateGenerator() {
}

RawMeasurementGraph RGBHeartRateGenerator::getHeartRate() {

    {
        FrameSharedLockedRGB slf = _rgbfs->getFrame();
        _did->drawImage(std::get<1>(slf));
    }

    RawMeasurementGraph rmg;
    rmg.push_back(RawMeasurement(1.0, 1.0));
    return rmg;
}

}  // namespace hrm

