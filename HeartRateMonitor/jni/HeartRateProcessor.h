/*
 * HeartRateProcessor.h
 *
 *  Created on: 24 но€б. 2013 г.
 *      Author: Admin
 */

#ifndef HEARTRATEPROCESSOR_H_
#define HEARTRATEPROCESSOR_H_

namespace hrm {

class HeartRateProcessor {
public:
    HeartRateProcessor();
    virtual ~HeartRateProcessor();

    bool start();
    void stop();

};

} /* namespace hrm */

#endif /* HEARTRATEPROCESSOR_H_ */
