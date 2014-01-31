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
#include "IImageDrawer.h"

namespace hrm {

class HeartRateProcessor {
public:
    HeartRateProcessor(boost::shared_ptr<RGBFrameSource> fs, boost::shared_ptr<IImageDrawer> drawer);
    virtual ~HeartRateProcessor();

    bool start();
    void stop();

private:
    void body();

    boost::thread _hrpThread;
    boost::tuples::tuple<boost::mutex, boost::condition_variable, bool> _start;

    boost::shared_ptr<RGBFrameSource> _rgbfs;
    boost::shared_ptr<IImageDrawer> _drawer;
};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
