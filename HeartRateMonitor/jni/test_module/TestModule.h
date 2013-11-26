/*
 * TestModule.h
 *
 *  Created on: 26 нояб. 2013 г.
 *      Author: pavel
 */

#ifndef TESTMODULE_H_
#define TESTMODULE_H_

#include "IModule.h"

namespace hrm {

class TestModule: public IModule
{
public:
    TestModule();
    virtual ~TestModule();

    virtual void update();
};

} /* namespace hrm */

#endif /* TESTMODULE_H_ */
