/*
 * HeartRateCounter.h
 *
 *  Created on: Feb 14, 2014
 *      Author: pavel
 */

#ifndef HEARTRATECOUNTER_H_
#define HEARTRATECOUNTER_H_

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

#include "IHeartRateGenerator.h"
#include "IHeartRateNumber.h"
#include "IHeartRateVisualizer.h"

namespace hrm {

class HeartRateCounter {
public:
    HeartRateCounter(
            IHeartRateGenerator::Ptr hrGenerator,
            IHeartRateNumber::Ptr hrNumber,
            IHeartRateVisualizer::Ptr hrVisualizer);
    virtual ~HeartRateCounter();

    bool start();

private:
    IHeartRateGenerator::Ptr _hrg;
    IHeartRateNumber::Ptr _hrn;
    IHeartRateVisualizer::Ptr _hrv;

    boost::thread _thread;
    void threadBody();
};

}  // namespace hrm

#endif /* HEARTRATECOUNTER_H_ */
