/*
 * LinuxLog.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef ILINUXLOG_H_
#define ILINUXLOG_H_

#include "ILog.h"

namespace hrm {

class LinuxLog: public ILog {
public:
    LinuxLog();
    virtual ~LinuxLog();

    virtual void DEBUG(const std::string& message);
    virtual void INFO(const std::string& message);
    virtual void ERROR(const std::string& message);
    virtual void WARN(const std::string& message);

private:
};

}  // namespace hrm

#endif /* ILINUXLOG_H_ */
