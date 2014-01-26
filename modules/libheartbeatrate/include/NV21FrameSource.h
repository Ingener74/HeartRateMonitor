/*
 * NV21FrameSource.h
 *
 *  Created on: Jan 26, 2014
 *      Author: pavel
 */

#ifndef NV21FRAMESOURCE_H_
#define NV21FRAMESOURCE_H_

#include "IFrameSource.h"

namespace hrm {

class NV21FrameSource: public IFrameSource {
public:
    NV21FrameSource();
    virtual ~NV21FrameSource();

    virtual LockedFrame getFrame();

    virtual void putFrame(uint16_t rows, uint16_t cols, uint8_t * data);

private:
    Frame _frame;
    boost::mutex _frameMutex;
};

}  // namespace hrm

#endif /* NV21FRAMESOURCE_H_ */
