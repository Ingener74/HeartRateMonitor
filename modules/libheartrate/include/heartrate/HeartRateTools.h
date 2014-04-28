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

namespace hrm {

class HeartRateTools {
public:
    typedef shared_ptr<HeartRateTools> Ptr;

    static Ptr instance();
    virtual ~HeartRateTools();

    ILog::Ptr getLog();

    void pushLog(ILog::Ptr log);
    void popLog();

    static int32_t rountUpToNextPowerOfTwo(int32_t x);

private:
    HeartRateTools();
    std::list<ILog::Ptr> _log;
};

}  // namespace hrm

#endif /* HEARTRATETOOLS_H_ */
