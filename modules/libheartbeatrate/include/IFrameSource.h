/*
 * IFrameSource.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef IFRAMESOURCE_H_
#define IFRAMESOURCE_H_

#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include "HeartBeatRateTypes.h"

namespace hrm {

typedef boost::tuple<
        boost::shared_ptr<boost::unique_lock<boost::mutex> >,
        Frame> LockedFrame;

class IFrameSource{
public:
    virtual ~IFrameSource(){}

    virtual LockedFrame getFrame() = 0;

protected:
    IFrameSource(){}
};

}  // namespace hrm



#endif /* IFRAMESOURCE_H_ */
