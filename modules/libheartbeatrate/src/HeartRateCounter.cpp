/*
 * HeartRateCounter.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include "HeartRateTools.h"
#include "HeartRateCounter.h"

namespace hrm {

HeartRateCounter::HeartRateCounter(
        IHeartRateGenerator::Ptr hrGenerator,
        IHeartRateNumber::Ptr hrNumber,
        IHeartRateVisualizer::Ptr hrVisualizer):
                _hrg(hrGenerator), _hrn(hrNumber), _hrv(hrVisualizer){
}

HeartRateCounter::~HeartRateCounter() {
    HeartRateTools::instance()->getLog()->DEBUG("HeartRateCounter::~HeartRateCounter()");
    _thread.join();
}

bool HeartRateCounter::start() {
    _thread = std::thread([this](){
        while(1){
            RawMeasurementGraph hrRawGraph = _hrg->getHeartRate();
            MeasurementGraph hrGraph;
            HeartRateValue hrNumber = 70;

            /* calculate heart rate */

            _hrn->setHeartRateNumber(hrNumber);
            _hrv->visualizeHeartRate(hrGraph);
        }
    });
    return true;
}

}  // namespace hrm

