/*
 * IHeartRateNumber.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATENUMBER_H_
#define IHEARTRATENUMBER_H_

#include <HeartRate/types/Types.h>

namespace hrm
{

class IHeartRateNumber
{
public:
    using Ptr = std::shared_ptr<IHeartRateNumber> ;

    virtual ~IHeartRateNumber()
    {
    }

    virtual void setHeartRate(HrmHeartRate heartRate) = 0;

protected:
    IHeartRateNumber()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATENUMBER_H_ */
