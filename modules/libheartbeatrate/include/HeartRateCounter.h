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
    HeartRateCounter(boost::shared_ptr<IHeartRateGenerator> hrGenerator,
            boost::shared_ptr<IHeartRateNumber> hrNumber,
            boost::shared_ptr<IHeartRateVisualizer> hrVisualizer);
    virtual ~HeartRateCounter();

    bool start();

private:
    boost::shared_ptr<IHeartRateGenerator> _hrg;
    boost::shared_ptr<IHeartRateNumber> _hrn;
    boost::shared_ptr<IHeartRateVisualizer> _hrv;

    boost::thread _thread;
    void threadBody();
};

}  // namespace hrm

#endif /* HEARTRATECOUNTER_H_ */
