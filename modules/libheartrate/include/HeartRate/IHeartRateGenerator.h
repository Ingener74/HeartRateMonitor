/*
 * IHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEGENERATOR_H_
#define IHEARTRATEGENERATOR_H_

#include <HeartRate/types/Types.h>

namespace hrm
{

typedef double HeartValue;

class IHeartRateGenerator
{
public:
    using Ptr = std::shared_ptr<IHeartRateGenerator>;

    virtual ~IHeartRateGenerator()
    {
    }

    virtual HrmMeasurement getHeartMeasurementValue() = 0;

protected:
    IHeartRateGenerator()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATEGENERATOR_H_ */
