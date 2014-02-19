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

#include <android/bitmap.h>

#include <HeartBeatRateTypes.h>
#include <HeartBeatRateDefines.h>
#include <HeartRateProcessor.h>
#include <ImageFormat.h>
#include <RGBFrameSource.h>
#include <IImageDrawer.h>

#include <HeartRateCounter.h>
#include <SimpleHeartRateNumber.h>
#include <SimpleHeartRateGenerator.h>
#include <SimpleHeartRateVisualizer.h>
#include <HeartRateTools.h>

#include "HeartRateMonitorPreview.h"

boost::shared_ptr<hrm::NV21FrameSource> nv21;
boost::shared_ptr<hrm::HeartRateProcessor> hrp;

boost::shared_ptr<hrm::HeartRateCounter> heartRateCounter;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LLDEBUG("JNI_OnLoad(JavaVM* vm, void* reserved)");
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}
void JNI_OnUnload(JavaVM* vm, void* reserved){
    LLDEBUG("JNI_OnUnload");
}

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv* JNIEnv_, jobject self) {

    hrm::TimeCounter::instance();
    hrm::HeartRateTools::instance()->getLog()->INFO("native start");

//    nv21 = boost::shared_ptr<hrm::NV21FrameSource>(new hrm::NV21FrameSource());
//    boost::shared_ptr<hrm::RGBFrameSource> rgbfs(new hrm::RGBFrameSource(nv21));
//    boost::shared_ptr<hrm::IImageDrawer> heartRateOutput(new HeartRateMonitorPreviewJava(JNIEnv_, self));

    boost::shared_ptr<hrm::IHeartRateGenerator> hrGenerator(
            new hrm::SimpleHeartRateGenerator());
    boost::shared_ptr<hrm::IHeartRateNumber> hrNumber(
            new hrm::SimpleHeartRateNumber());
    boost::shared_ptr<hrm::IHeartRateVisualizer> hrVisualizer(
            new hrm::SimpleHeartRateVisualizer());
    heartRateCounter = boost::shared_ptr<hrm::HeartRateCounter>(
            new hrm::HeartRateCounter(
                    hrGenerator,
                    hrNumber,
                    hrVisualizer
                    ));

    hrm::HeartRateTools::instance()->getLog()->INFO("native started");

//    return true;
    return heartRateCounter->start();
}

void Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStop(
        JNIEnv* JNIEnv_, jobject self) {

    hrm::HeartRateTools::instance()->getLog()->INFO("native stop");

    heartRateCounter->stop();

    hrm::HeartRateTools::instance()->getLog()->INFO("native stoped");

//    JNIEnv_->DeleteGlobalRef(HeartRateMonitorPreviewThis);
}

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativePassImage(
        JNIEnv* JNIEnv_, jobject self,
        jint rows, jint cols, jint type, jbyteArray data) {

    static bool nv21_error = false;
    if(!nv21 ){
        if(!nv21_error){
            LLWARN("NV21 is null");
            nv21_error = true;
        }
        return false;
    }

    jboolean imageDataIsCopy = false;
    jbyte* imageData = JNIEnv_->GetByteArrayElements(data, &imageDataIsCopy);

    /*
     * measure time and pass image in processor
     */
    boost::tuple<hrm::TimeStamp, hrm::ElapsedTime> ts =
            hrm::TimeCounter::instance()->getTimeStampExt();
    LLINFO("current time = %.2f ms, fps = %.1f", ts.get<0>(), 1000.0 / ts.get<1>());

    LLINFO("%d x %d, type = %s, %p",
            cols,
            rows,
            hrm::AndroidImageFormat::instance()->getImageFormatString(type).c_str(),
            imageData
            );

    nv21->putFrame(uint16_t(rows), uint16_t(cols), (uint8_t *)imageData, ts.get<0>());

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
