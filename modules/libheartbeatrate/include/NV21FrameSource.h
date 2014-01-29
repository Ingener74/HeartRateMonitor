/*
 * NV21FrameSource.h
 *
 *  Created on: Jan 26, 2014
 *      Author: pavel
 */

#ifndef NV21FRAMESOURCE_H_
#define NV21FRAMESOURCE_H_

#include <boost/thread/condition_variable.hpp>

#include "IFrameSource.h"

namespace hrm {

class NV21FrameSource: public IFrameSource {
public:
    NV21FrameSource();
    virtual ~NV21FrameSource();

    virtual SharedLockedFrame getFrame();

    virtual void putFrame(uint16_t rows, uint16_t cols, uint8_t * data);

private:
    Frame _frame;
    boost::shared_mutex _frameMutex;
    boost::condition_variable _frameCond;
};

}  // namespace hrm

#endif /* NV21FRAMESOURCE_H_ */
