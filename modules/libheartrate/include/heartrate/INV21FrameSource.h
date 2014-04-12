/*
 * INV21FrameSource.h
 *
 *  Created on: Mar 15, 2014
 *      Author: pavel
 */

#ifndef INV21FRAMESOURCE_H_
#define INV21FRAMESOURCE_H_

#include <heartrate/HeartBeatRateTypes.h>

namespace hrm {

class INV21FrameSource {
public:
	typedef shared_ptr<INV21FrameSource> Ptr;

    virtual ~INV21FrameSource() {
    }

    virtual LockedFrame<BitsPerPixelImageFormat>::Shared getFrame() = 0;

protected:
    INV21FrameSource() {
    }
};

}  // namespace hrm

#endif /* INV21FRAMESOURCE_H_ */