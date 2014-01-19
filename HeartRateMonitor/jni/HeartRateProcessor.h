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

#include "IFrameSource.h"

namespace hrm {

class HeartRateProcessor {
public:
    HeartRateProcessor(IFrameSource* fs);
    virtual ~HeartRateProcessor();

    bool start();
    void stop();

private:
    void body();

    boost::thread _hrpThread;
    boost::tuples::tuple<boost::mutex, boost::condition_variable, bool> _start;

    IFrameSource* _frameSource;
};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
