/*
 * HeartRateTools.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef HEARTRATETOOLS_H_
#define HEARTRATETOOLS_H_

#include <HeartRate/HeartRateCommon.h>

namespace hrm {

class HeartRateTools {
public:
    typedef shared_ptr<HeartRateTools> Ptr;

    static Ptr instance();
    virtual ~HeartRateTools();

    static int32_t rountUpToNextPowerOfTwo(int32_t x);

private:
    HeartRateTools();
};

}  // namespace hrm

#endif /* HEARTRATETOOLS_H_ */
