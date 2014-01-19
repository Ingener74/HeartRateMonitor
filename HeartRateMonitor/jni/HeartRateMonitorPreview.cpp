/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include <string>
#include <map>

#include <boost/smart_ptr.hpp>

#include "HeartRateMonitorPreview.h"

#include "hrm_defines.h"
#include "HeartRateProcessor.h"
#include "ImageFormat.h"
#include "Types.h"

boost::shared_ptr<hrm::HeartRateProcessor> hrp;
hrm::TimeCounter tc;

boost::shared_ptr<hrm::IFrameSource> frameSource;

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv* JNIEnv_, jobject thiz) {

    frameSource = boost::shared_ptr<hrm::IFrameSource>(new ConcreteFrameSource());

    I("native start");
    hrp = boost::shared_ptr<hrm::HeartRateProcessor>(new hrm::HeartRateProcessor(frameSource.get()));
    return hrp->start();
}

void Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStop(
        JNIEnv* JNIEnv_, jobject thiz) {

    I("native stop");

    if(!hrp){
        E("native stoped");
        return;
    }
    hrp->stop();

    I("native stoped");
}

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativePassImage(
        JNIEnv* JNIEnv_, jobject thiz,
        jint rows, jint cols, jint type, jbyteArray data) {
    jboolean imageDataIsCopy = false;
    jbyte* imageData = JNIEnv_->GetByteArrayElements(data, &imageDataIsCopy);

    /*
     * measure time and pass image in processor
     */
    double delta = tc.timeElapsedInMS();
    I("delta time = %.2f ms, fps = %.1f", delta, 1000.0 / delta);

    I("%d x %d, type = %s, %p",
            cols,
            rows,
            hrm::ImageFormat::instance()->getImageFormatString(type).c_str(),
            imageData
            );



    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
