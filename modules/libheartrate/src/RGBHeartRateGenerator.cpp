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

RawMeasurementGraph RGBHeartRateGenerator::getHeartRate() {

    RawMeasurement rawValue;

    {
        FrameSharedLockedRGB slf = _rgbfs->getFrame();

        _rgbfd->drawFrame(slf.get<1>());

        RGB* p = slf.get<1>().getData();

        NormalizedMeasurementValue nmv = 0.0;

        for (int i = 0, imax = slf.get<1>().getFormat().rect.area(); i < imax; ++i) {
            nmv += /*p++->r + p++->g +*/ p++->b; // best graph
//            nmv += p++->r/* + p++->g + p++->b*/;
        }

        rawValue = RawMeasurement(slf.get<1>().getTimeStamp(), nmv);
    }

    _rawGraph.push_back(rawValue);

    for(;;){
        RawMeasurement back = _rawGraph.back();
        RawMeasurement front = _rawGraph.front();

        TimeStamp diff = back.get<0>() - front.get<0>();

//        int32_t next2_1 = HeartRateTools::rountUpToNextPowerOfTwo(_rawGraph.size() - 1);
//        int32_t next2_2 = HeartRateTools::rountUpToNextPowerOfTwo(_rawGraph.size());
//        HeartRateTools::instance()->getLog()->DEBUG((format
//                ("rgb heart rate next power of two = %1% - %2%, current = %3%") % next2_1 % next2_2 % int(_rawGraph.size())
//                ).str());

        if( diff > 2000.0 && (
                HeartRateTools::rountUpToNextPowerOfTwo(_rawGraph.size() - 1) !=
                HeartRateTools::rountUpToNextPowerOfTwo(_rawGraph.size())   )
                ){
            _rawGraph.pop_front();
        }else{
            break;
        }
    }

    return _rawGraph;
}

}  // namespace hrm

