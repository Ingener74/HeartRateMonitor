/*
 * IHeartRateGenerator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEGENERATOR_H_
#define IHEARTRATEGENERATOR_H_

#include <heartrate/types/Exception.h>
#include <heartrate/types/Types.h>

namespace hrm
{

typedef double HeartValue;

class IHeartRateGenerator
{
public:
    typedef shared_ptr<IHeartRateGenerator> Ptr;

    virtual ~IHeartRateGenerator()
    {
    }

    virtual HrmMeasurement getHeartMeasurementValue()
            throw (HRGenerateException) = 0;

protected:
    IHeartRateGenerator()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATEGENERATOR_H_ */
