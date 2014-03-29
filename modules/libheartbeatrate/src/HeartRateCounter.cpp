/*
 * HeartRateCounter.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include "heartratemonitor/HeartRateTools.h"
#include "heartratemonitor/HeartRateCounter.h"

namespace hrm {

HeartRateCounter::HeartRateCounter(
        IHeartRateGenerator::Ptr hrGenerator,
        IHeartRateNumber::Ptr hrNumber,
        IHeartRateVisualizer::Ptr hrVisualizer):
                _hrg(hrGenerator), _hrn(hrNumber), _hrv(hrVisualizer){
}

HeartRateCounter::~HeartRateCounter() {
    HeartRateTools::instance()->getLog()->DEBUG("HeartRateCounter::~HeartRateCounter()");
    _thread.interrupt();
    _thread.join();
}

bool HeartRateCounter::start() {
    // TODO lambda problem deadlock
    _thread = boost::thread(boost::bind(&HeartRateCounter::threadFunc, this));
    return true;
}

void HeartRateCounter::threadFunc(void) {
    try {
        while(1){
            RawMeasurementGraph hrRawGraph = _hrg->getHeartRate();
            MeasurementGraph hrGraph;
            HeartRateValue hrNumber = 70;

            /* calculate heart rate */

            _hrn->setHeartRateNumber(hrNumber);
            _hrv->visualizeHeartRate(hrGraph);

            boost::this_thread::interruption_point();
        }
    } catch (const boost::thread_interrupted& e) {
    }
}

}  // namespace hrm

