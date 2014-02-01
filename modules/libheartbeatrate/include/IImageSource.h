/*
 * IImageSource.h
 *
 *  Created on: Feb 1, 2014
 *      Author: pavel
 */

#ifndef IIMAGESOURCE_H_
#define IIMAGESOURCE_H_

#include <boost/tuple/tuple.hpp>
#include <boost/smart_ptr.hpp>

namespace hrm {

typedef boost::tuple<
        boost::shared_ptr<boost::unique_lock<boost::shared_mutex> >,
        Image
        > UniqueLockedImage;
typedef boost::tuple<
        boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >,
        Image
        > SharedLockedImage;

class IImageSource {
public:
    virtual ~IImageSource() {
    }

    virtual SharedLockedImage getImage() = 0;

protected:
    IImageSource() {
    }
};

}  // namespace hrm



#endif /* IIMAGESOURCE_H_ */
