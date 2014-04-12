/*
 * RGBFrameSource.h
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#ifndef RGBFRAMESOURCE_H_
#define RGBFRAMESOURCE_H_

#include <heartrate/IRGBFrameSource.h>
#include <heartrate/INV21FrameSource.h>

namespace hrm {

class RGBFrameSource: public IRGBFrameSource {
public:
    RGBFrameSource(INV21FrameSource::Ptr nv21);
    virtual ~RGBFrameSource();

    virtual FrameSharedLockedRGB getFrame();
private:
    FrameRGB _frame;
    boost::shared_mutex _frameMutex;
    INV21FrameSource::Ptr _nv21;
};

}  // namespace hrm

#endif /* RGBFRAMESOURCE_H_ */
