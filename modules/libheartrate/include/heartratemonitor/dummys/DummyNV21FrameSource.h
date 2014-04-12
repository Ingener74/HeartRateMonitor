/*
 * DummyNV21FrameSource.h
 *
 *  Created on: Apr 6, 2014
 *      Author: ingener
 */

#ifndef DUMMYNV21FRAMESOURCE_H_
#define DUMMYNV21FRAMESOURCE_H_

#include <heartratemonitor/INV21FrameSource.h>

namespace hrm {
namespace dummys {

class DummyNV21FrameSource: public INV21FrameSource {
public:
    DummyNV21FrameSource();
    virtual ~DummyNV21FrameSource();

    virtual LockedFrame<BitsPerPixelImageFormat>::Shared getFrame();
private:
    Frame<BitsPerPixelImageFormat> _frame;
    boost::shared_mutex _frameMutex;

    thread _thread;
    void threadFunc();
    boost::condition_variable_any _frameCond;
};

} /* namespace dummys */
} /* namespace hrm */

#endif /* DUMMYNV21FRAMESOURCE_H_ */
