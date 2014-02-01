/*
 * HeartRateProcessor.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#include "HeartRateProcessor.h"
#include "HeartBeatRateDefines.h"

namespace hrm {

HeartRateProcessor::HeartRateProcessor(boost::shared_ptr<RGBFrameSource> fs) :
        _rgbfs(fs){
}

HeartRateProcessor::~HeartRateProcessor() {
    _hrpThread.interrupt();
    _hrpThread.join();
}

void HeartRateProcessor::body() {
    if(boost::this_thread::interruption_enabled())
        D("boost::this_thread::interruption_enabled()");
    try {
        I("heart rate processor whiskers");
//        {
//            boost::unique_lock<boost::mutex> lock(_start.get<0>());
//
//
//
//        }
//        _start.get<2>() = true;
//        _start.get<1>().notify_all();
        I("heart rate processor body");
        while(1){
            boost::this_thread::interruption_point();

            {
                /*
                 * wait frame
                 */
                SharedLockedFrame lockedFrame = _rgbfs->getFrame();

                /*
                 * process
                 */
            }

        }
    } catch (const boost::thread_interrupted& e) {
        I("heart rate processor tail");
    }
}

SharedLockedImage HeartRateProcessor::getImage() {

}

} /* namespace hrm */

