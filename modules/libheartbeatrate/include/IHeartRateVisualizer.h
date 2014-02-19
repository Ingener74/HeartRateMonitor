/*
 * IHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IHEARTRATEVISUALIZER_H_
#define IHEARTRATEVISUALIZER_H_

#include "HeartBeatRateTypes.h"

namespace hrm {

class IHeartRateVisualizer {
public:
    virtual ~IHeartRateVisualizer(){}

    virtual void visualizeHeartRate(Image heartRateGraph) = 0;

protected:
    IHeartRateVisualizer(){}
};

}  // namespace hrm



#endif /* IHEARTRATEVISUALIZER_H_ */
