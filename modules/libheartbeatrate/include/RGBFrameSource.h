/*
 * RGBFrameSource.h
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#ifndef RGBFRAMESOURCE_H_
#define RGBFRAMESOURCE_H_

#include "IRGBFrameSource.h"
#include "NV21FrameSource.h"

namespace hrm {

class RGBFrameSource: public IRGBFrameSource {
public:
    RGBFrameSource(boost::shared_ptr<NV21FrameSource> nv21);
    virtual ~RGBFrameSource();

    virtual FrameSharedLockedRGB getFrame();
private:
    FrameRGB _frame;
    boost::shared_mutex _frameMutex;
    boost::shared_ptr<NV21FrameSource> _nv21;
};

}  // namespace hrm

#endif /* RGBFRAMESOURCE_H_ */
