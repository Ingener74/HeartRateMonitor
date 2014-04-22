/*
 * HeartRateCounter.h
 *
 *  Created on: Feb 14, 2014
 *      Author: pavel
 */

#ifndef HEARTRATECOUNTER_H_
#define HEARTRATECOUNTER_H_

#include <heartrate/IHeartRateGenerator.h>
#include <heartrate/IHeartRateRecognizer.h>
#include <heartrate/IHeartRateNumber.h>
#include <heartrate/IHeartRateVisualizer.h>

namespace hrm
{

class HeartRateCounter
{
public:
    typedef boost::shared_ptr<HeartRateCounter> Ptr;

    HeartRateCounter(IHeartRateGenerator::Ptr hrGenerator,
            IHeartRateRecognizer::Ptr hrRecognizer,
            IHeartRateNumber::Ptr hrNumber,
            IHeartRateVisualizer::Ptr hrVisualizer);
    virtual ~HeartRateCounter();

    bool start();
    void run();

private:
    IHeartRateGenerator::Ptr _hrg;
    IHeartRateRecognizer::Ptr _hrr;
    IHeartRateNumber::Ptr _hrn;
    IHeartRateVisualizer::Ptr _hrv;

    boost::thread _thread;
    void threadFunc(void);
};

}  // namespace hrm

#endif /* HEARTRATECOUNTER_H_ */
