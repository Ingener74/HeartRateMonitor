/*
 * RGBFrameSource.h
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#ifndef RGBFRAMESOURCE_H_
#define RGBFRAMESOURCE_H_

#include "NV21FrameSource.h"

namespace hrm {

class RGBFrameSource : public IFrameSource{
public:
    RGBFrameSource(boost::shared_ptr<NV21FrameSource> nv21);
    virtual ~RGBFrameSource();

    virtual SharedLockedFrame getFrame();
private:
    Frame _frame;
    boost::shared_mutex _frameMutex;
    boost::shared_ptr<NV21FrameSource> _nv21;
};

}  // namespace hrm



#endif /* RGBFRAMESOURCE_H_ */
