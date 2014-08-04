/*
 * Types.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <HeartRate/HeartRateCommon.h>

namespace hrm
{

//                                                // comment

using HrmTimeStamp = double;                      // time stamp
using HrmElapsedTime = double;

struct HrmMeasurement
{
    using Value = double;                         // image brightness

    HrmTimeStamp timeStamp;
    Value value;
};
std::ostream& operator<<(std::ostream& sout, const HrmMeasurement& m);

using HrmMeasurementGraph =
        std::deque<HrmMeasurement>;               // heart beat graph

struct HrmHeartRate
{
    enum class State
    {
        Valid, Invalid
    };
    using Value = int;                            // heart beat in minute

    State state;
    Value value;
};
std::ostream& operator<<(std::ostream& sout, const HrmHeartRate& hr);

using HrmFrequency = double;
using HrmFrequencyGraph = std::vector<HrmFrequency>;

}  // namespace hrm

#endif /* TYPES_H_ */
