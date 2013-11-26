/*
 * IModule.h
 *
 *  Created on: 26 нояб. 2013 г.
 *      Author: pavel
 */

#ifndef IMODULE_H_
#define IMODULE_H_

namespace hrm {

class IModule
{
public:
    IModule();
    virtual ~IModule();

    virtual void update() = 0;
};

} /* namespace hrm */

#endif /* IMODULE_H_ */
