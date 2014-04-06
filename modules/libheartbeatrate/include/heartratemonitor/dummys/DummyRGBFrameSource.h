/*
 * DummyRGBFrameSource.h
 *
 *  Created on: Apr 6, 2014
 *      Author: ingener
 */

#ifndef DUMMYRGBFRAMESOURCE_H_
#define DUMMYRGBFRAMESOURCE_H_

#include "heartratemonitor/IRGBFrameSource.h"

namespace hrm {

namespace dummys {

class DummyRGBFrameSource: public IRGBFrameSource {
public:
    DummyRGBFrameSource();
    virtual ~DummyRGBFrameSource();

    virtual FrameSharedLockedRGB getFrame();
private:
    FrameRGB _frame;
    shared_mutex _frameMutex;
};

}  // namespace dummys

} /* namespace hrm */

#endif /* DUMMYRGBFRAMESOURCE_H_ */
