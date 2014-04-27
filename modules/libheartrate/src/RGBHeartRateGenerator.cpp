/*
 * RGBHeartRateGenerator.cpp
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#include <heartrate/HeartRateTools.h>
#include <heartrate/RGBHeartRateGenerator.h>

namespace hrm {

RGBHeartRateGenerator::RGBHeartRateGenerator(
        IRGBFrameSource::Ptr rgbFrameSource,
        IRGBFrameDrawer::Ptr rgbFrameDrawer) :
        _rgbfs(rgbFrameSource), _rgbfd(rgbFrameDrawer){
}

RGBHeartRateGenerator::~RGBHeartRateGenerator() {
    HeartRateTools::instance()->getLog()->DEBUG(
            "RGBHeartRateGenerator::~RGBHeartRateGenerator()");
}

HrmMeasurement RGBHeartRateGenerator::getHeartMeasurementValue()
        throw (HRGenerateException)
{
    HrmMeasurement rawValue;
    {
        FrameSharedLockedRGB slf = _rgbfs->getFrame();

        _rgbfd->drawFrame(slf.get<1>());

        RGB* p = slf.get<1>().getData();

        HrmMeasurement::Value nmv = 0.0;

        for (int i = 0, imax = slf.get<1>().getFormat().rect.area(); i < imax; ++i) {
            nmv += /*p++->r + p++->g +*/ p++->b; // best graph
        }

        ImageRect ir = slf.get<1>().getFormat().rect;
        rawValue = {slf.get<1>().getTimeStamp(), nmv / (255 * ir.area())};
    }
    return rawValue;
}

}  // namespace hrm

