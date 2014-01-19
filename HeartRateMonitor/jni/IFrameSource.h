/*
 * IFrameSource.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef IFRAMESOURCE_H_
#define IFRAMESOURCE_H_

#include <boost/thread/mutex.hpp>

namespace hrm {

class IFrameSource{
public:
    virtual ~IFrameSource(){}

    virtual boost::shared_lock<boost::mutex> getFrame() = 0;

    virtual void setFrame() = 0;

protected:
    IFrameSource(){}
};

}  // namespace hrm



#endif /* IFRAMESOURCE_H_ */
