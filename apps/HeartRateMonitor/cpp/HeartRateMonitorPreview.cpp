/*
 * HeartRateMonitorPreview.cpp
 *
 *  Created on: 23 нояб. 2013 г.
 *      Author: pavel
 */

#include <string>

#include <android/bitmap.h>

#include <heartrate/HeartRate.h>

#include <ImageViewHeartRateVisualizer.h>
#include <ImageViewFrameDrawer.h>

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

    try {

        TimeCounter::instance();
        HRM_INFO("native start");

        nv21 = make_shared<NV21FrameSource>();

//      IRGBFrameDrawer::Ptr(new RGB2PNGDataBaseFrameDrawer("/sdcard/test_db"))
        auto hrGenerator = make_shared<RGBHeartRateGenerator>(
                make_shared<RGBFrameSource>(nv21),
                make_shared<ImageViewFrameDrawer>(JNIEnv_, self, "drawCameraPreview"));

        auto hrNumber = make_shared<mock::MockHeartRateNumber>();
        auto hrVisualizer = make_shared<ImageViewHeartRateVisualizer>(JNIEnv_, self, "drawHeartRate");
        auto hrRecog = make_shared<mock::MockHeartRateRecognizer>();

        heartRateCounter = make_shared<HeartRateCounter>(
                hrGenerator, hrRecog, hrNumber, hrVisualizer);

        HRM_INFO("native started");

    } catch (const std::runtime_error& e) {
        HRM_ERROR(format("runtime error in hrm native start: %1%") % e.what());
        return false;
    }
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

//    return false;

    if (!nv21) {
        return false;
    }

    jboolean imageDataIsCopy = false;
    jbyte* imageData = JNIEnv_->GetByteArrayElements(data, &imageDataIsCopy);

    /*
     * measure time and pass image in nv21 frame source
     */
    using namespace hrm;
    try {
//        HeartRateTools::instance()->getLog()->DEBUG((
//                format("type = %1%") % type
//                ).str());

        auto ts = TimeCounter::instance()->getTimeStampExt();

        dynamic_cast<NV21FrameSource&>(*nv21).putFrame(
                static_cast<uint16_t>(rows),
                static_cast<uint16_t>(cols),
                reinterpret_cast<uint8_t *>(imageData),
                ts.get<0>()
                );

    } catch (const std::runtime_error& e) {
        HRM_ERROR(format("put frame error: %1%") % e.what());
    }

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
