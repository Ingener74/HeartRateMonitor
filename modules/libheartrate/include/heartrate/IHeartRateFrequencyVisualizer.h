/*
 * IHeartRateFrequencyVisualizer.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef IHEARTRATEFREQUENCYVISUALIZER_H_
#define IHEARTRATEFREQUENCYVISUALIZER_H_

#include <heartrate/HeartRateCommon.h>
#include <heartrate/types/Exception.h>
#include <heartrate/HeartBeatRateTypes.h>

namespace hrm {

class IHeartRateFrequencyVisualizer {
public:
    typedef shared_ptr<IHeartRateFrequencyVisualizer> Ptr;

    virtual ~IHeartRateFrequencyVisualizer() {
    }

    virtual void visualize(const FrequencyGraph& graph)
            throw (HRVisualizeException) = 0;
protected:
    IHeartRateFrequencyVisualizer() {
    }
};

}  // namespace hrm

#endif /* IHEARTRATEFREQUENCYVISUALIZER_H_ */
