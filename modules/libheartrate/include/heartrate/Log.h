/*
 * Log.h
 *
 *  Created on: Apr 28, 2014
 *      Author: pavel
 */

#ifndef LOG_H_
#define LOG_H_

#include <sstream>

namespace hrm
{

enum LEVEL
{
    DEBUG, INFO, ERR, WARN
};
class Log: public std::stringstream
{
public:
    Log(LEVEL level = DEBUG);

    virtual ~Log();

private:
    LEVEL _l;
};

} /* namespace hrm */

#endif /* LOG_H_ */
