/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include <string>
#include <map>
#include <list>

#include <boost/lambda/lambda.hpp>
#include <boost/smart_ptr.hpp>

#include <HeartBeatRateTypes.h>
#include <HeartBeatRateDefines.h>
#include <HeartRateProcessor.h>
#include <ImageFormat.h>
#include <RGBFrameSource.h>

#include "HeartRateMonitorPreview.h"

hrm::TimeCounter tc;
boost::shared_ptr<hrm::NV21FrameSource> nv21;
boost::shared_ptr<hrm::HeartRateProcessor> hrp;

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv* JNIEnv_, jobject thiz) {

    nv21 = boost::shared_ptr<hrm::NV21FrameSource>(new hrm::NV21FrameSource());
    boost::shared_ptr<hrm::RGBFrameSource> rgbfs(new hrm::RGBFrameSource(nv21));

    I("native start");
    hrp = boost::shared_ptr<hrm::HeartRateProcessor>(new hrm::HeartRateProcessor(rgbfs));
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

    nv21->putFrame(uint16_t(rows), uint16_t(cols), (uint8_t *)imageData);

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
