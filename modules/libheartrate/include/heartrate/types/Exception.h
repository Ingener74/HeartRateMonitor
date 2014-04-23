/*
 * Exception.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <heartrate/HeartRateCommon.h>

namespace hrm
{

/*
 * HeartRateException
 *  |
 *  |-> HRFrameSourceException
 *  |-> HRNumberException
 *  |-> HRVisualizeException
 *  |-> HRRecognitionException
 *  |-> HRDrawException
 */

class HeartRateException: public std::runtime_error
{
public:
    HeartRateException(const std::string& message) :
            std::runtime_error(message)
    {
    }
    virtual ~HeartRateException() throw ()
    {
    }
};

class HRFrameSourceException: public HeartRateException
{
public:
    HRFrameSourceException(const std::string& message) :
            HeartRateException(message)
    {
    }
    virtual ~HRFrameSourceException() throw ()
    {
    }
};

class HRNumberException: public HeartRateException
{
public:
    HRNumberException(const std::string& message) :
            HeartRateException(message)
    {
    }
    virtual ~HRNumberException() throw ()
    {
    }
};

class HRVisualizeException: public HeartRateException
{
public:
    HRVisualizeException(const std::string& message) :
            HeartRateException(message)
    {
    }
    virtual ~HRVisualizeException() throw ()
    {
    }
};

class HRRecognitionException: public HeartRateException
{
public:
    HRRecognitionException(const std::string& message) :
            HeartRateException(message)
    {
    }
    virtual ~HRRecognitionException() throw ()
    {
    }
};

class HRDrawException: public HeartRateException
{
public:
    HRDrawException(const std::string& message) :
            HeartRateException(message)
    {
    }
    virtual ~HRDrawException() throw ()
    {
    }
};

}  // namespace hrm

#endif /* EXCEPTION_H_ */
