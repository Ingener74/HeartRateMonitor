/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include <string>
#include <memory>

#include <android/bitmap.h>

#include <heartratemonitor/HeartBeatRateTypes.h>
#include <heartratemonitor/HeartBeatRateDefines.h>
#include <heartratemonitor/RGBFrameSource.h>
#include <heartratemonitor/NV21FrameSource.h>

#include <heartratemonitor/HeartRateCounter.h>
#include <heartratemonitor/SimpleHeartRateNumber.h>
#include <heartratemonitor/HeartRateTools.h>

#include <heartratemonitor/SimpleHeartRateVisualizer.h>
#include <ImageViewHeartRateVisualizer.h>

#include <heartratemonitor/SimpleHeartRateGenerator.h>
#include <heartratemonitor/RGBHeartRateGenerator.h>

#include <ImageViewImageDrawer.h>

#include "HeartRateMonitorPreview.h"

hrm::INV21FrameSource::Ptr nv21;
boost::shared_ptr<hrm::HeartRateCounter> heartRateCounter;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LLDEBUG("JNI_OnLoad(JavaVM* vm, void* reserved)");
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}
void JNI_OnUnload(JavaVM* vm, void* reserved) {
    LLDEBUG("JNI_OnUnload");
}

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStart(
        JNIEnv* JNIEnv_, jobject self) {

    hrm::TimeCounter::instance();
    hrm::HeartRateTools::instance()->getLog()->INFO("native start");

    nv21 = hrm::INV21FrameSource::Ptr(new hrm::NV21FrameSource());
    hrm::IRGBFrameSource::Ptr rgbfs(new hrm::RGBFrameSource(nv21));

    hrm::IRGBImageDrawer::Ptr debugImageDrawer(
            new hrm::ImageViewImageDrawer(JNIEnv_, self));

    hrm::IHeartRateVisualizer::Ptr hrVisualizer;
    hrm::IHeartRateGenerator::Ptr hrGenerator;

//    hrGenerator = boost::shared_ptr<hrm::IHeartRateGenerator>(
//            new hrm::SimpleHeartRateGenerator());
    hrGenerator = hrm::IHeartRateGenerator::Ptr(
            new hrm::RGBHeartRateGenerator(rgbfs, debugImageDrawer));

    hrm::IHeartRateNumber::Ptr hrNumber(new hrm::SimpleHeartRateNumber());

//    hrVisualizer = boost::shared_ptr<hrm::IHeartRateVisualizer>(
//            new hrm::ImageViewHeartRateVisualizer(JNIEnv_, self));
    hrVisualizer = hrm::IHeartRateVisualizer::Ptr(
            new hrm::SimpleHeartRateVisualizer());

    heartRateCounter = boost::shared_ptr<hrm::HeartRateCounter>(
            new hrm::HeartRateCounter(hrGenerator, hrNumber, hrVisualizer));

    hrm::HeartRateTools::instance()->getLog()->INFO("native started");

    return heartRateCounter->start();
}

void Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativeStop(
        JNIEnv* JNIEnv_, jobject self) {
    heartRateCounter.reset();
    nv21.reset();
}

jboolean Java_com_shnayder_heartratemonitor_HeartRateMonitorPreview_hrmNativePassImage(
        JNIEnv* JNIEnv_, jobject self, jint rows, jint cols, jint type,
        jbyteArray data) {

    if (!nv21) {
        return false;
    }

    jboolean imageDataIsCopy = false;
    jbyte* imageData = JNIEnv_->GetByteArrayElements(data, &imageDataIsCopy);

    /*
     * measure time and pass image in nv21 frame source
     */
    boost::tuple<hrm::TimeStamp, hrm::ElapsedTime> ts =
            hrm::TimeCounter::instance()->getTimeStampExt();
//    LLINFO("current time = %.2f ms, fps = %.1f", boost::get<0>(ts),
//            1000.0 / boost::get<1>(ts));

    dynamic_cast<hrm::NV21FrameSource&>(*nv21).putFrame(uint16_t(rows), uint16_t(cols), (uint8_t *) imageData,
            ts.get<0>());

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
