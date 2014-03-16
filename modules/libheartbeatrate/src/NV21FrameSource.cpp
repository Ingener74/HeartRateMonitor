/*
 * NV21FrameSource.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: pavel
 */

#include "HeartBeatRateDefines.h"

#include "NV21FrameSource.h"

namespace hrm {

NV21FrameSource::NV21FrameSource() {
}

NV21FrameSource::~NV21FrameSource() {
}

LockedFrame<BitsPerPixelImageFormat>::Shared NV21FrameSource::getFrame(){
    {
        boost::unique_lock<boost::shared_mutex> lock(_frameMutex);
        _frameCond.wait(lock);
    }
    LockedFrame<BitsPerPixelImageFormat>::Shared lf(
            std::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
            new boost::shared_lock<boost::shared_mutex>(_frameMutex)), _frame);
    return lf;
}

void NV21FrameSource::putFrame(uint16_t rows, uint16_t cols, uint8_t * data,
        TimeStamp timeStamp) {
    {
        boost::unique_lock<boost::shared_mutex> lock(_frameMutex);

        ImageRect inputRect = ImageRect(rows, cols);
        if(_frame.getFormat().rect != inputRect){
            _frame = Frame<BitsPerPixelImageFormat>(
                    BitsPerPixelImageFormat(inputRect, 12));
        }
        /*
         * copy original
         */
        uint32_t bytesToCopy = _frame.getFormat().size();
        uint8_t * s = data, * d = _frame.getData();
        for (int i = 0; i < bytesToCopy; ++i) {
            *d++ = *s++;
        }

        _frame.setTimeStamp(timeStamp);
    }
    _frameCond.notify_one();
}

}  // namespace hrm

