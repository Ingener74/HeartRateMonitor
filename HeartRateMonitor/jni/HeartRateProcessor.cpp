/*
 * HeartRateProcessor.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Admin
 */

#include <HeartRateProcessor.h>

#include <TestModule.h>

namespace hrm {

HeartRateProcessor::HeartRateProcessor(): _test(0){
    _test = new TestModule();
}

HeartRateProcessor::~HeartRateProcessor() {
    delete _test;
    _test = 0;
}

bool hrm::HeartRateProcessor::start() {
    return true;
}

void hrm::HeartRateProcessor::stop() {
}

} /* namespace hrm */

