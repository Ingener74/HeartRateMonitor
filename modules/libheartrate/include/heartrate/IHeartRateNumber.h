/*
 * IHeartRateNumber.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATENUMBER_H_
#define IHEARTRATENUMBER_H_

#include <heartrate/types/Exception.h>
#include <heartrate/types/Types.h>

namespace hrm
{

class IHeartRateNumber
{
public:
    typedef shared_ptr<IHeartRateNumber> Ptr;

    virtual ~IHeartRateNumber()
    {
    }

    virtual void setHeartRate(HrmHeartRate heartRate)
            throw (HRNumberException) = 0;

protected:
    IHeartRateNumber()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATENUMBER_H_ */
