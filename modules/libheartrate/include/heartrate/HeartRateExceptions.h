/*
 * HeartRateExceptions.h
 *
 *  Created on: Apr 6, 2014
 *      Author: ingener
 */

#ifndef HEARTRATEEXCEPTIONS_H_
#define HEARTRATEEXCEPTIONS_H_

#include <heartrate/HeartRateCommon.h>

namespace hrm {

/*
 * Exceptions
 *
 * HRException
 *  |
 *  |-> HRGetFrameException
 *  |-> HRDrawFrameException
 */
class HRException: public std::runtime_error {
public:
    HRException(const std::string& message) :
            std::runtime_error(message) {
    }
    virtual ~HRException() {
    }
};

class HRGetFrameException: public HRException {
public:
    HRGetFrameException(const std::string& message) :
            HRException(message) {
    }
    virtual ~HRGetFrameException() {
    }
};

class HRDrawFrameException: public HRException {
    HRDrawFrameException(const std::string& message) :
            HRException(message) {
    }
    virtual ~HRDrawFrameException() {
    }
};

}  // namespace hrm

#endif /* HEARTRATEEXCEPTIONS_H_ */
