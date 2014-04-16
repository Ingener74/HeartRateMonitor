/*
 * HeartRateTools.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef HEARTRATETOOLS_H_
#define HEARTRATETOOLS_H_

#include <heartrate/HeartRateCommon.h>
#include <heartrate/ILog.h>

#define HRM_DEBUG(mes) hrm::HeartRateTools::instance()->getLog()->DEBUG(mes);
#define HRM_INFO(mes) hrm::HeartRateTools::instance()->getLog()->INFO(mes);
#define HRM_ERROR(mes) hrm::HeartRateTools::instance()->getLog()->ERROR(mes);
#define HRM_WARN(mes) hrm::HeartRateTools::instance()->getLog()->WARN(mes);

namespace hrm {

class HeartRateTools {
public:
    typedef shared_ptr<HeartRateTools> Ptr;

    static Ptr instance();
    virtual ~HeartRateTools();

    void setLog(ILog::Ptr log);
    ILog::Ptr getLog();

    static int32_t rountUpToNextPowerOfTwo(int32_t x);

private:
    HeartRateTools();
    ILog::Ptr _log;
};

}  // namespace hrm

#endif /* HEARTRATETOOLS_H_ */
