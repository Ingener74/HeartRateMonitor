/*
 * IRGBFrameDrawer.h
 *
 *  Created on: Apr 2, 2014
 *      Author: ingener
 */

#ifndef IRGBFRAMEDRAWER_H_
#define IRGBFRAMEDRAWER_H_

#include <heartrate/HeartBeatRateTypes.h>
#include <heartrate/types/Exception.h>

namespace hrm
{

class IRGBFrameDrawer
{
public:
    typedef shared_ptr<IRGBFrameDrawer> Ptr;

    virtual ~IRGBFrameDrawer()
    {
    }

    virtual void drawFrame(FrameRGB frame) throw (HRDrawException) = 0;

protected:
    IRGBFrameDrawer()
    {
    }
};

}  // namespace hrm

#endif /* IRGBFRAMEDRAWER_H_ */
