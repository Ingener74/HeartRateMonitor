/*
 * Exception.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <heartrate/HeartRateCommon.h>

namespace hrm {

/*
 * HeartRateException
 *  |
 *  |-> HRFrameSourceException
 *  |-> HRNumberException
 *  |-> HRVisualizeException
 *  |-> HRRecognitionException
 */

class HeartRateException: public std::runtime_error {
public:
    HeartRateException(const std::string& message) :
            std::runtime_error(message) {
    }
    virtual ~HeartRateException() throw () {
    }
};

class HRFrameSourceException: public HeartRateException {
public:
    HRFrameSourceException(const std::string& message) :
            HeartRateException(message) {
    }
    virtual ~HRFrameSourceException() throw () {
    }
};

class HRNumberException: public HeartRateException {
public:
    HRNumberException(const std::string& message) :
            HeartRateException(message) {
    }
    virtual ~HRNumberException() {
    }
};

class HRVisualizeException: public HeartRateException {
public:
    HRVisualizeException(const std::string& message) :
            HeartRateException(message) {
    }
    virtual ~HRVisualizeException() {
    }
};

class HRRecognitionException: public HeartRateException {
public:
    HRRecognitionException(const std::string& message) :
            HeartRateException(message) {
    }
    virtual ~HRRecognitionException() {
    }
};

}  // namespace hrm

#endif /* EXCEPTION_H_ */
