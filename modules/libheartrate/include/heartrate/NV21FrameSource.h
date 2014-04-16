/*
 * NV21FrameSource.h
 *
 *  Created on: Jan 26, 2014
 *      Author: pavel
 */

#ifndef NV21FRAMESOURCE_H_
#define NV21FRAMESOURCE_H_

#include <heartrate/INV21FrameSource.h>

namespace hrm {

class NV21FrameSource: public INV21FrameSource {
public:
    typedef shared_ptr<NV21FrameSource> Ptr;

    NV21FrameSource();
    virtual ~NV21FrameSource();

    virtual LockedFrame<BitsPerPixelImageFormat>::Shared getFrame();

    virtual void putFrame(uint16_t rows, uint16_t cols, uint8_t * data,
            TimeStamp timeStamp);

private:
    Frame<BitsPerPixelImageFormat> _frame;
    shared_mutex _frameMutex;
    condition_variable_any _frameCond;
};

}  // namespace hrm

#endif /* NV21FRAMESOURCE_H_ */
