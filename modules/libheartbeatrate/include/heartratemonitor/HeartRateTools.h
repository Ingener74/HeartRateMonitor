/*
 * HeartRateTools.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef HEARTRATETOOLS_H_
#define HEARTRATETOOLS_H_

#include <boost/smart_ptr.hpp>
#include "ILog.h"

namespace hrm {

class HeartRateTools {
public:
    static boost::shared_ptr<HeartRateTools> instance();
    virtual ~HeartRateTools();

    virtual ILog::Ptr getLog();

private:
    HeartRateTools();
    ILog::Ptr _log;
};

}  // namespace hrm



#endif /* HEARTRATETOOLS_H_ */
