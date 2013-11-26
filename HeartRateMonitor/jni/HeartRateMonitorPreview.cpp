/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include "HeartRateMonitorPreview.h"

#include "hrm_defines.h"
#include "HeartRateProcessor.h"

hrm::HeartRateProcessor * hrp = 0;

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv*, jobject) {

    I("native start");

    hrp = new hrm::HeartRateProcessor();
    return hrp->start();
}

void Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStop(
        JNIEnv*, jobject) {

    I("native stop");

    if(hrp)
        hrp->stop();
    myFree(hrp);

    I("native stoped");
}
