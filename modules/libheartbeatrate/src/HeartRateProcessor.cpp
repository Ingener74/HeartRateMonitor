/*
 * HeartRateProcessor.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#include "HeartRateProcessor.h"
#include "HeartBeatRateDefines.h"

namespace hrm {

HeartRateProcessor::HeartRateProcessor(boost::shared_ptr<RGBFrameSource> fs,
        boost::shared_ptr<IImageDrawer> drawer) :
        _rgbfs(fs), _drawer(drawer){
}

HeartRateProcessor::~HeartRateProcessor() {
}

bool hrm::HeartRateProcessor::start() {
    I("heart rate processor start");
    _start.get<2>() = false;
    boost::unique_lock<boost::mutex> lock(_start.get<0>());
    _hrpThread = boost::thread(boost::bind(&HeartRateProcessor::body, this));
    _start.get<1>().wait(lock);
    return _start.get<2>();
}

void hrm::HeartRateProcessor::stop() {
    I("heart rate processor stop");
    _hrpThread.interrupt();
    _hrpThread.join();
    I("heart rate processor stoped");
}

void HeartRateProcessor::body() {
    if(boost::this_thread::interruption_enabled())
        D("boost::this_thread::interruption_enabled()");
    try {
        I("heart rate processor whiskers");
        {
            boost::unique_lock<boost::mutex> lock(_start.get<0>());



        }
        _start.get<2>() = true;
        _start.get<1>().notify_all();
        I("heart rate processor body");
        while(1){
            boost::this_thread::interruption_point();

            {
                /*
                 * wait frame
                 */
                LockedFrame lockedFrame = _rgbfs->getFrame();

                /*
                 * process
                 */
            }

        }
    } catch (const boost::thread_interrupted& e) {
        I("heart rate processor tail");
    }
}

} /* namespace hrm */

