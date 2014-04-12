/*
 * MockNV21FrameSource.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#include <heartrate/mocks/MockNV21FrameSource.h>

namespace hrm {
namespace mock {

const int TEST_ROWS = 144;
const int TEST_COLS = 176;
const int TEST_BITS_PER_PIXEL = 12;
const int TEST_ROW = 100;

MockNV21FrameSource::MockNV21FrameSource(): _frame(BitsPerPixelImageFormat(ImageRect(TEST_ROWS, TEST_COLS),
        TEST_BITS_PER_PIXEL)) {
    uint8_t * data = _frame.getData();
    for (int i = 0, imax = _frame.getFormat().size(); i < imax; ++i) {
        *data++ = 0;
    }
    data = _frame.getData();
    for (int i = 0, imax = TEST_ROW; i < imax; ++i) {
        for (int j = 0, jmax = TEST_ROW; j < jmax; ++j) {
            *(data + i * _frame.getFormat().rect._cols + j) = i;
        }
    }
//    _thread = thread(bind(&DummyNV21FrameSource::threadFunc, this));
}

MockNV21FrameSource::~MockNV21FrameSource() {
//    _thread.interrupt();
//    _thread.join();
}

LockedFrame<BitsPerPixelImageFormat>::Shared MockNV21FrameSource::getFrame() {
    //    unique_lock<shared_mutex> lock(_frameMutex);
    //    _frameCond.wait(lock);

        this_thread::sleep(posix_time::milliseconds(30));

        LockedFrame<BitsPerPixelImageFormat>::Shared lf(
                boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                        new boost::shared_lock<boost::shared_mutex>(_frameMutex)),
                _frame);
        return lf;
}

void MockNV21FrameSource::threadFunc() {
    using namespace boost;

    try {

        for (;;) {
            this_thread::interruption_point();

            {
                unique_lock<shared_mutex> lock(_frameMutex);
            }
            _frameCond.notify_all();

            this_thread::sleep(posix_time::milliseconds(30));
        }

    } catch (const thread_interrupted& e) {
    } catch (const exception& e) {
    }
}

} /* namespace mock */
} /* namespace hrm */
