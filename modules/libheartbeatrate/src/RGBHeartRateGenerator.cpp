/*
 * RGBHeartRateGenerator.cpp
 *
 *  Created on: 22 февр. 2014 г.
 *      Author: ingener
 */

#include <algorithm>

#include <boost/format.hpp>

#include "heartratemonitor/HeartRateTools.h"
#include "heartratemonitor/RGBHeartRateGenerator.h"

namespace hrm {

RGBHeartRateGenerator::RGBHeartRateGenerator(
        IRGBFrameSource::Ptr rgbFrameSource/*,
        IRGBImageDrawer::Ptr debugImageDrawer*/) :
            _rgbfs(rgbFrameSource)/*, _did(debugImageDrawer)*/{
}

RGBHeartRateGenerator::~RGBHeartRateGenerator() {
}

RawMeasurementGraph RGBHeartRateGenerator::getHeartRate() {

    RawMeasurement rawValue;

    {
        FrameSharedLockedRGB slf = _rgbfs->getFrame();
//        _did->drawImage(slf.get<1>());

        RGB* p = slf.get<1>().getData();

        HeartRateValue hrv = 0;
        NormalizedMeasurementValue nmv = 0.0;

        for (int i = 0, imax = slf.get<1>().getFormat().rect.area(); i < imax; ++i) {
            hrv += p++->r + p++->g + p++->b;
        }

        hrv /= slf.get<1>().getFormat().rect.area();

        nmv = hrv / 255.0;

        rawValue = RawMeasurement(slf.get<1>().getTimeStamp(), nmv);
    }

    _rawGraph.push_back(rawValue);

    for(;;){
        RawMeasurement back = _rawGraph.back();
        RawMeasurement front = _rawGraph.front();

        TimeStamp diff = back.get<0>() - front.get<0>();

//        HeartRateTools::instance()->getLog()->DEBUG((
//                boost::format("diff = %1%") % diff
//                ).str());

        if( diff > 2000.0){
            _rawGraph.pop_front();
        }else{
            break;
        }
    }

    return _rawGraph;

//    RawMeasurementGraph rmg;
//    rmg.push_back(RawMeasurement(1.0, 1.0));
//    return rmg;
}

}  // namespace hrm

