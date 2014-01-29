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

SharedLockedFrame hrm::NV21FrameSource::getFrame() {
    {
        boost::unique_lock<boost::shared_mutex> lock(_frameMutex);
        _frameCond.wait(lock);
    }
    SharedLockedFrame lf(boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
            new boost::shared_lock<boost::shared_mutex>(_frameMutex)), _frame);
    return lf;
}

void NV21FrameSource::putFrame(uint16_t rows, uint16_t cols, uint8_t * data) {
    {
        boost::unique_lock<boost::mutex> lock(_frameMutex);

        FrameRect inputRect = FrameRect(rows, cols);
        if(_frame.getFrameFormat()._rect != inputRect){
            _frame = Frame(FrameFormat(inputRect, 12));
        }
        /*
         * copy original
         */
        uint32_t bytesToCopy = _frame.getFrameFormat()._rect.area();
        uint8_t * s = data, * d = _frame.getData();
        for (int i = 0; i < bytesToCopy; ++i) {
            *d++ = *s++;
        }
    }
    _frameCond.notify_one();
}

}  // namespace hrm

