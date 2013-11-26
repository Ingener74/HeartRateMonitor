/*
 * HeartRateProcessor.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#include <HeartRateProcessor.h>

#include <TestModule.h>

namespace hrm {

HeartRateProcessor::HeartRateProcessor(): _test(0), _hrpStop(false){
    _test = new TestModule();
}

HeartRateProcessor::~HeartRateProcessor() {
    delete _test;
    _test = 0;
}

bool hrm::HeartRateProcessor::start() {
    _hrpThread = boost::thread(boost::bind(&HeartRateProcessor::body, this));
    return true;
}

void hrm::HeartRateProcessor::stop() {
    {
        boost::mutex::scoped_lock lock(_hrpStopMutex);
        _hrpStop = true;
    }
    _hrpThread.join();
}

void HeartRateProcessor::body(){
    for(;;){
        {
            boost::mutex::scoped_lock lock(_hrpStopMutex);
            if(_hrpStop)
                break;
        }

        usleep(30 * 1000);
    }
}

} /* namespace hrm */

