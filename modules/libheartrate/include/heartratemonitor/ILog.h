/*
 * ILog.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef ILOG_H_
#define ILOG_H_

#include <string>
#include <boost/smart_ptr.hpp>

namespace hrm {

class ILog {
public:
	typedef boost::shared_ptr<ILog> Ptr;

	virtual ~ILog() {
	}

	virtual void DEBUG(const std::string& message) = 0;
	virtual void INFO(const std::string& message) = 0;
	virtual void ERROR(const std::string& message) = 0;
	virtual void WARN(const std::string& message) = 0;

protected:
	ILog() {
	}
};

}  // namespace hrm

#endif /* ILOG_H_ */