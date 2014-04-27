/*
 * HeartRateCounter.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <heartrate/HeartRateTools.h>
#include <heartrate/HeartRateCounter.h>

namespace hrm
{

HeartRateCounter::HeartRateCounter(
        IHeartRateGenerator::Ptr hrGenerator,
        IHeartRateRecognizer::Ptr hrRecognizer,
        IHeartRateNumber::Ptr hrNumber,
        IHeartRateVisualizer::Ptr hrVisualizer) :
        _hrg(hrGenerator), _hrr(hrRecognizer),
        _hrn(hrNumber), _hrv(hrVisualizer)
{
}

HeartRateCounter::~HeartRateCounter()
{
    _thread.interrupt();
    _thread.join();
    HRM_DEBUG("HeartRateCounter::~HeartRateCounter()");
}

bool HeartRateCounter::start()
{
    // TODO lambda problem deadlock
    _thread = boost::thread(boost::bind(&HeartRateCounter::threadFunc, this));
    return true;
}

void HeartRateCounter::calcHeartRate()
{
    HRM_DEBUG("calc heart rate 1");

    HrmMeasurement hrMeasurement = _hrg->getHeartMeasurementValue();
    HRM_DEBUG("calc heart rate 2");

    HrmHeartRate heartRate = {HrmHeartRate::State::Valid, 70};
    /* calculate heart rate */
    HRM_DEBUG("calc heart rate 3");

    _measGraph.push_back(hrMeasurement);
    if(_measGraph.size() > 64){
        _measGraph.pop_front();
    }
    HRM_DEBUG("calc heart rate 4");

    heartRate = _hrr->recognizeHeartRateValue(hrMeasurement);
    HRM_DEBUG("calc heart rate 5");

    _hrv->visualizeHeartRate(_measGraph);
    HRM_DEBUG("calc heart rate 6");

    _hrn->setHeartRate(heartRate);
    HRM_DEBUG("calc heart rate 7");
}

void HeartRateCounter::threadFunc(void)
{
    try
    {
        while (1)
        {
            calcHeartRate();

            boost::this_thread::interruption_point();
        }
    }
    catch (const boost::thread_interrupted& e)
    {
        HRM_DEBUG("thread interupted");
    }
    catch (const std::runtime_error& e)
    {
        HRM_ERROR(format("runtime error in heart rate counter: %1%") % e.what());
    }
    catch (...)
    {
        HRM_ERROR("fatal error in heart rate counter");
    }
}

void hrm::HeartRateCounter::run()
{
    while (1)
    {
        calcHeartRate();
    }
}

}  // namespace hrm

