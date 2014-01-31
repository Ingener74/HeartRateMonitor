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
#include <IImageDrawer.h>

#include "HeartRateMonitorPreview.h"

boost::shared_ptr<hrm::NV21FrameSource> nv21;
boost::shared_ptr<hrm::HeartRateProcessor> hrp;

class HeartRateMonitorPreviewJava: public hrm::IImageDrawer {
public:
    HeartRateMonitorPreviewJava() {
    }
    virtual ~HeartRateMonitorPreviewJava() {
    }
    virtual void drawImage(hrm::Image image) {
    }
};

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv* JNIEnv_, jobject thiz) {

    hrm::TimeCounter::instance();

    nv21 = boost::shared_ptr<hrm::NV21FrameSource>(new hrm::NV21FrameSource());
    boost::shared_ptr<hrm::RGBFrameSource> rgbfs(new hrm::RGBFrameSource(nv21));

    boost::shared_ptr<hrm::IImageDrawer> heartRateOutput(new HeartRateMonitorPreviewJava());

    I("native start");
    hrp = boost::shared_ptr<hrm::HeartRateProcessor>(new hrm::HeartRateProcessor(rgbfs, heartRateOutput));
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
    boost::tuple<hrm::TimeStamp, hrm::ElapsedTime> ts =
            hrm::TimeCounter::instance()->getTimeStampExt();
    I("current time = %.2f ms, fps = %.1f", ts.get<0>(), 1000.0 / ts.get<1>());
//    I("current time = %.2f ms, fps = %.1f", ts.get<0>(), ts.get<1>());

    I("%d x %d, type = %s, %p",
            cols,
            rows,
            hrm::AndroidImageFormat::instance()->getImageFormatString(type).c_str(),
            imageData
            );

    nv21->putFrame(uint16_t(rows), uint16_t(cols), (uint8_t *)imageData, ts.get<0>());

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
