/*
 * AndroidLog.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef ANDROIDLOG_H_
#define ANDROIDLOG_H_

#include <heartrate/ILog.h>

namespace hrm {

class AndroidLog: public ILog {
public:
    AndroidLog();
    virtual ~AndroidLog();

    virtual void DEBUG(const std::string& message);
    virtual void INFO(const std::string& message);
    virtual void ERR(const std::string& message);
    virtual void WARN(const std::string& message);

    virtual void DEBUG(const basic_format<char>& messages);
    virtual void INFO(const basic_format<char>& messages);
    virtual void ERR(const basic_format<char>& messages);
    virtual void WARN(const basic_format<char>& messages);

private:
};

}  // namespace hrm

#endif /* ANDROIDLOG_H_ */
