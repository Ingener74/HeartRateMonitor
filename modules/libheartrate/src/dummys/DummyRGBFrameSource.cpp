/*
 * DummyRGBFrameSource.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: ingener
 */

#include <unistd.h>

#include <heartrate/dummys/DummyRGBFrameSource.h>

namespace hrm {

namespace dummys {

DummyRGBFrameSource::DummyRGBFrameSource() :
        _frame(TypeImageFormat<RGB>(ImageRect(144, 176))) {
    RGB * data = _frame.getData();
    for (int i = 0, imax = 100; i < imax; ++i) {
        for (int j = 0, jmax = 100; j < jmax; ++j) {
            *(data + i*_frame.getFormat().rect._cols + j) = {
                static_cast<uint8_t>(i), static_cast<uint8_t>(j), 0
            };
        }
    }
}

DummyRGBFrameSource::~DummyRGBFrameSource() {
}

FrameSharedLockedRGB DummyRGBFrameSource::getFrame() {

    usleep(30000); // FIXME change to boost thread sleeping

    FrameSharedLockedRGB lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)),
            _frame);
    return lockedFrame;
}

}  // namespace dummys

} /* namespace hrm */
