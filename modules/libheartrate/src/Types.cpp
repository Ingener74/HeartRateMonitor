/*
 * Types.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: ingener
 */

#include <heartrate/types/Types.h>

namespace hrm
{

std::ostream& operator<<(std::ostream& sout, const HrmMeasurement& m)
{
    return (sout << "[ " << std::setw(12) << m.timeStamp << "] = " << m.value);
}

std::ostream& operator<<(std::ostream& sout, const HrmHeartRate& hr)
{
    return (hr.state == HrmHeartRate::State::Valid) ?
            (sout << "HeartRate: valid and " << hr.value << " beats per minute") :
            (sout << "HeartRate: invalid");
}

}  // namespace hrm

