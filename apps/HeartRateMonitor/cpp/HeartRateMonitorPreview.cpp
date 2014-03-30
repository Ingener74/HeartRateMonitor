/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include <string>

#include <android/bitmap.h>

#include <heartratemonitor/HeartBeatRateTypes.h>
#include <heartratemonitor/HeartBeatRateDefines.h>
#include <heartratemonitor/NV21FrameSource.h>
#include <heartratemonitor/RGBFrameSource.h>
#include <heartratemonitor/RGBHeartRateGenerator.h>

#include <heartratemonitor/HeartRateCounter.h>
#include <heartratemonitor/HeartRateTools.h>

#include <heartratemonitor/SimpleHeartRateNumber.h>
#include <heartratemonitor/SimpleHeartRateVisualizer.h>
#include <heartratemonitor/SimpleHeartRateGenerator.h>

#include <ImageViewHeartRateVisualizer.h>
#include <ImageViewImageDrawer.h>

#include "HeartRateMonitorPreview.h"

hrm::INV21FrameSource::Ptr nv21;
hrm::HeartRateCounter::Ptr heartRateCounter;

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

    using namespace hrm;

    TimeCounter::instance();
    HeartRateTools::instance()->getLog()->INFO("native start");

    nv21 = INV21FrameSource::Ptr(new NV21FrameSource());
    IRGBFrameSource::Ptr rgbfs(new RGBFrameSource(nv21));

    IHeartRateVisualizer::Ptr hrVisualizer;
    IHeartRateGenerator::Ptr hrGenerator;

    hrGenerator = IHeartRateGenerator::Ptr(new RGBHeartRateGenerator(rgbfs));

    IHeartRateNumber::Ptr hrNumber(new SimpleHeartRateNumber());

    hrVisualizer = IHeartRateVisualizer::Ptr(
            new ImageViewHeartRateVisualizer(JNIEnv_, self));

    heartRateCounter = HeartRateCounter::Ptr(
            new HeartRateCounter(hrGenerator, hrNumber, hrVisualizer));

    HeartRateTools::instance()->getLog()->INFO("native started");

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
    using namespace hrm;
    boost::tuple<TimeStamp, ElapsedTime> ts =
            TimeCounter::instance()->getTimeStampExt();

    dynamic_cast<NV21FrameSource&>(*nv21).putFrame(uint16_t(rows), uint16_t(cols), (uint8_t *) imageData,
            ts.get<0>());

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
