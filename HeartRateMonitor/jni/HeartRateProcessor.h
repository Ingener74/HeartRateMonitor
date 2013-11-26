/*
 * HeartRateProcessor.h
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#ifndef HEARTRATEPROCESSOR_H_
#define HEARTRATEPROCESSOR_H_

#include <IModule.h>

namespace hrm {

class HeartRateProcessor {
public:
    HeartRateProcessor();
    virtual ~HeartRateProcessor();

    bool start();
    void stop();

private:
    IModule* _test;
};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
