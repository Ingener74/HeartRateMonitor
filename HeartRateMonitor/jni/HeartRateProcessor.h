/*
 * HeartRateProcessor.h
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#ifndef HEARTRATEPROCESSOR_H_
#define HEARTRATEPROCESSOR_H_

#include <IModule.h>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace hrm {

class HeartRateProcessor {
public:
    HeartRateProcessor();
    virtual ~HeartRateProcessor();

    bool start();
    void stop();

private:
    void body();

    IModule* _test;

    boost::thread _hrpThread;
    boost::mutex  _hrpStopMutex;
    bool          _hrpStop;
};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
