/*
 * RGBFrameSource.h
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#ifndef RGBFRAMESOURCE_H_
#define RGBFRAMESOURCE_H_

#include "IFrameSource.h"

namespace hrm {

class RGBFrameSource : public IFrameSource{
public:
    RGBFrameSource();
    virtual ~RGBFrameSource();

    virtual boost::shared_lock<boost::mutex> getFrame();

    virtual void setFrame();

private:
};

}  // namespace hrm



#endif /* RGBFRAMESOURCE_H_ */
