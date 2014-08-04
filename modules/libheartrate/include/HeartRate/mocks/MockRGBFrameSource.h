/*
 * MockRGBFrameSource.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef MOCKRGBFRAMESOURCE_H_
#define MOCKRGBFRAMESOURCE_H_

#include <heartrate/HeartRateCommon.h>
#include <heartrate/IRGBFrameSource.h>

namespace hrm {
namespace mock {

class MockRGBFrameSource: public IRGBFrameSource {
public:
    MockRGBFrameSource();
    virtual ~MockRGBFrameSource();

    virtual FrameSharedLockedRGB getFrame() throw (HRFrameSourceException);

private:
    FrameRGB _frame;
    shared_mutex _frameMutex;
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKRGBFRAMESOURCE_H_ */
