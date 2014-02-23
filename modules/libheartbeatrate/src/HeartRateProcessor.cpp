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
    try {
        LLINFO("heart rate processor whiskers");


        LLINFO("heart rate processor body");
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
        LLINFO("heart rate processor tail");
    }
}

SharedLockedImage HeartRateProcessor::getImage() {
}

} /* namespace hrm */

