/*
 * IRGBFrameSource.h
 *
 *  Created on: Mar 15, 2014
 *      Author: pavel
 */

#ifndef IRGBFRAMESOURCE_H_
#define IRGBFRAMESOURCE_H_

#include <memory>

#include "HeartBeatRateTypes.h"

namespace hrm {

class IRGBFrameSource {
public:
    typedef std::shared_ptr<IRGBFrameSource> Ptr;

    virtual ~IRGBFrameSource() {
    }

    virtual FrameSharedLockedRGB getFrame() = 0;
protected:
    IRGBFrameSource() {
    }
};

}  // namespace hrm

#endif /* IRGBFRAMESOURCE_H_ */
