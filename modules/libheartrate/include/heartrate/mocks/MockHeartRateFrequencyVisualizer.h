/*
 * MockHeartRateFrequencyVisualizer.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef MOCKHEARTRATEFREQUENCYVISUALIZER_H_
#define MOCKHEARTRATEFREQUENCYVISUALIZER_H_

#include <heartrate/HeartRateCommon.h>
#include <heartrate/IHeartRateFrequencyVisualizer.h>

namespace hrm
{
namespace mock
{

class MockHeartRateFrequencyVisualizer: public IHeartRateFrequencyVisualizer
{
public:
    MockHeartRateFrequencyVisualizer();
    virtual ~MockHeartRateFrequencyVisualizer();

    virtual void visualize(const HrmFrequencyGraph& graph)
            throw (HRVisualizeException);
};

} /* namespace mock */
} /* namespace hrm */

#endif /* MOCKHEARTRATEFREQUENCYVISUALIZER_H_ */
