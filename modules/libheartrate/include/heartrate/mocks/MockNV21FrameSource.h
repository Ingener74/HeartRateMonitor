/*
 * MockNV21FrameSource.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKNV21FRAMESOURCE_H_
#define MOCKNV21FRAMESOURCE_H_

#include <heartrate/INV21FrameSource.h>

namespace hrm {
namespace mock {

class MockNV21FrameSource: public INV21FrameSource {
public:
    MockNV21FrameSource();
    virtual ~MockNV21FrameSource();

    virtual LockedFrame<BitsPerPixelImageFormat>::Shared getFrame();

private:
    Frame<BitsPerPixelImageFormat> _frame;
    shared_mutex _frameMutex;

    thread _thread;
    void threadFunc();
    condition_variable_any _frameCond;
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKNV21FRAMESOURCE_H_ */
