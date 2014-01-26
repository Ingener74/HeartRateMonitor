/*
 * NV21FrameSource.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: pavel
 */

#include "HeartBeatRateDefines.h"

#include "NV21FrameSource.h"

namespace hrm {

hrm::NV21FrameSource::NV21FrameSource() {
}

hrm::NV21FrameSource::~NV21FrameSource() {
}

LockedFrame hrm::NV21FrameSource::getFrame() {
    LockedFrame lf(boost::shared_ptr<boost::unique_lock<boost::mutex> >(
            new boost::unique_lock<boost::mutex>(_frameMutex)), _frame);
    return lf;
}

void NV21FrameSource::putFrame(uint16_t rows, uint16_t cols, uint8_t * data) {
    boost::unique_lock<boost::mutex> lock(_frameMutex);
    /*
     * move
     */
    FrameRect inputRect = FrameRect(rows, cols);
    if(_frame.getFrameFormat()._rect != inputRect){
        _frame = Frame(FrameFormat(inputRect, 2));
    }
    D("uint16_t rows = %d, uint16_t cols = %d, uint8_t * data = %p", rows, cols, data);
}

}  // namespace hrm

