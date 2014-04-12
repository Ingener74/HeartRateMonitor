/*
 * MockRGBFrameSource.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#include <heartrate/mocks/MockRGBFrameSource.h>

namespace hrm {
namespace mock {

MockRGBFrameSource::MockRGBFrameSource() :
        _frame(TypeImageFormat<RGB>(ImageRect(144, 176))) {
}

MockRGBFrameSource::~MockRGBFrameSource() {
}

FrameSharedLockedRGB MockRGBFrameSource::getFrame() {

    this_thread::sleep(posix_time::milliseconds(30));

    FrameSharedLockedRGB lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)),
            _frame);
    return lockedFrame;
}

} /* namespace mock */
} /* namespace hrm */
