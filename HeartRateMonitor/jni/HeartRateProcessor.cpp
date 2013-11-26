/*
 * HeartRateProcessor.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#include <HeartRateProcessor.h>
#include "hrm_defines.h"

namespace hrm {

HeartRateProcessor::HeartRateProcessor(): _hrpStop(false){
}

HeartRateProcessor::~HeartRateProcessor() {
}

bool hrm::HeartRateProcessor::start() {
    I("heart rate processor start");
    _hrpThread = boost::thread(boost::bind(&HeartRateProcessor::body, this));
    return true;
}

void hrm::HeartRateProcessor::stop() {
    I("heart rate processor stop");
    {
        boost::mutex::scoped_lock lock(_hrpStopMutex);
        _hrpStop = true;
    }
    _hrpThread.join();
    I("heart rate processor stoped");
}

void HeartRateProcessor::body(){

    I("heart rate processor whiskers");

    for(;;){
        {
            boost::mutex::scoped_lock lock(_hrpStopMutex);
            if(_hrpStop)
                break;
        }

        usleep(30 * 1000);
    }
    I("heart rate processor tail");
}

} /* namespace hrm */

