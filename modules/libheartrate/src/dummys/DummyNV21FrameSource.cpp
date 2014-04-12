/*
 * DummyNV21FrameSource.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: ingener
 */

#include <unistd.h>

#include <heartrate/dummys/DummyNV21FrameSource.h>

namespace hrm {
namespace dummys {

const int TEST_ROWS = 144;
const int TEST_COLS = 176;
const int TEST_BITS_PER_PIXEL = 12;
const int TEST_ROW = 100;

DummyNV21FrameSource::DummyNV21FrameSource() :
        _frame(BitsPerPixelImageFormat(ImageRect(TEST_ROWS, TEST_COLS),
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

    using namespace boost;

//    _thread = thread(bind(&DummyNV21FrameSource::threadFunc, this));
}

DummyNV21FrameSource::~DummyNV21FrameSource() {
//    _thread.interrupt();
//    _thread.join();
}

LockedFrame<BitsPerPixelImageFormat>::Shared DummyNV21FrameSource::getFrame() {

    using namespace boost;

//    unique_lock<shared_mutex> lock(_frameMutex);
//    _frameCond.wait(lock);

    this_thread::sleep(posix_time::milliseconds(30));

    LockedFrame<BitsPerPixelImageFormat>::Shared lf(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)),
            _frame);
    return lf;
}

void hrm::dummys::DummyNV21FrameSource::threadFunc() {
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

} /* namespace dummys */
} /* namespace hrm */

