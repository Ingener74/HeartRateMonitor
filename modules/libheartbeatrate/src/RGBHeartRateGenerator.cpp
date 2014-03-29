/*
 * RGBHeartRateGenerator.cpp
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#include "heartratemonitor/HeartRateTools.h"
#include "heartratemonitor/RGBHeartRateGenerator.h"

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
        _did->drawImage(slf.get<1>());
    }

    RawMeasurementGraph rmg;
    rmg.push_back(RawMeasurement(1.0, 1.0));

    return rmg;
}

}  // namespace hrm

