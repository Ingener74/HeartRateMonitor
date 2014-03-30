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
        IRGBFrameSource::Ptr rgbFrameSource) :
        _rgbfs(rgbFrameSource) {
}

RGBHeartRateGenerator::~RGBHeartRateGenerator() {
}

RawMeasurementGraph RGBHeartRateGenerator::getHeartRate() {

    RawMeasurement rawValue;

    {
        FrameSharedLockedRGB slf = _rgbfs->getFrame();

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

        if( diff > 2000.0){
            _rawGraph.pop_front();
        }else{
            break;
        }
    }

    return _rawGraph;
}

}  // namespace hrm

