/*
 * Log.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: pavel
 */

#include <heartrate/HeartRateTools.h>
#include <heartrate/Log.h>

namespace hrm
{

Log::Log(LEVEL level) :
        _l(level)
{
}

Log::~Log()
{
    switch (_l)
    {
    case DEBUG:
        HeartRateTools::instance()->getLog()->DEBUG(str());
        break;
    case INFO:
        HeartRateTools::instance()->getLog()->INFO(str());
        break;
    case ERROR:
        HeartRateTools::instance()->getLog()->ERR(str());
        break;
    case WARN:
        HeartRateTools::instance()->getLog()->WARN(str());
        break;
    default:
        break;
    }
}

} /* namespace hrm */
