/*
 * IHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEVISUALIZER_H_
#define IHEARTRATEVISUALIZER_H_

#include <HeartRate/types/Types.h>

namespace hrm
{

class IHeartRateVisualizer
{
public:
    typedef shared_ptr<IHeartRateVisualizer> Ptr;

    virtual ~IHeartRateVisualizer()
    {
    }

    virtual void visualizeHeartRate(HrmMeasurementGraph heartRateMeasuredGraph)
            throw (HRVisualizeException)= 0;

protected:
    IHeartRateVisualizer()
    {
    }
};

}  // namespace hrm

#endif /* IHEARTRATEVISUALIZER_H_ */
