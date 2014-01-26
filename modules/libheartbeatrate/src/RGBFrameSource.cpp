/*
 * RGBFrameSource.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#include "RGBFrameSource.h"

namespace hrm {

hrm::RGBFrameSource::RGBFrameSource(boost::shared_ptr<NV21FrameSource> nv21) :
        _nv21(nv21) {
}

hrm::RGBFrameSource::~RGBFrameSource() {
}

LockedFrame RGBFrameSource::getFrame() {
    {
        LockedFrame lockedFrame = _nv21->getFrame();

        /*
         * convert nv21 to rgb
         */
    }
    LockedFrame lockedFrame(
            boost::shared_ptr<boost::unique_lock<boost::mutex> >(
                    new boost::unique_lock<boost::mutex>(_frameMutex)), _frame);
    return lockedFrame;
}

}  // namespace hrm

