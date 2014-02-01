/*
 * HeartRateProcessor.h
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#ifndef HEARTRATEPROCESSOR_H_
#define HEARTRATEPROCESSOR_H_

#include <utility>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "RGBFrameSource.h"
#include "IImageSource.h"

namespace hrm {

class HeartRateProcessor: public IImageSource {
public:
    HeartRateProcessor(boost::shared_ptr<RGBFrameSource> fs);
    virtual ~HeartRateProcessor();

    virtual SharedLockedImage getImage();

private:
    void body();

    boost::shared_ptr<RGBFrameSource> _rgbfs;

    boost::thread _hrpThread;
    Image _image;
};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
