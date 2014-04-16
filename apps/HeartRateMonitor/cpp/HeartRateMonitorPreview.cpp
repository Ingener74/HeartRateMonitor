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
        HeartRateTools::instance()->getLog()->INFO("native start");

        nv21 = INV21FrameSource::Ptr(
                new NV21FrameSource()
//                new dummys::DummyNV21FrameSource()
        );
        IRGBFrameSource::Ptr rgbfs(
                new RGBFrameSource(nv21)
//                new DummyRGBFrameSource()
        );

        IHeartRateGenerator::Ptr hrGenerator(new RGBHeartRateGenerator(
                rgbfs,
//                IRGBFrameDrawer::Ptr(new RGB2PNGDataBaseFrameDrawer("/sdcard/test_db"))
                IRGBFrameDrawer::Ptr(new ImageViewFrameDrawer(JNIEnv_, self, "drawCameraPreview"))
                ));

        IHeartRateNumber::Ptr hrNumber(new mock::MockHeartRateNumber());

        IHeartRateVisualizer::Ptr hrVisualizer = IHeartRateVisualizer::Ptr(
                new ImageViewHeartRateVisualizer(JNIEnv_, self, "drawHeartRate")
//                new SimpleHeartRateVisualizer()
        );

        heartRateCounter = HeartRateCounter::Ptr(
                new HeartRateCounter(hrGenerator, hrNumber, hrVisualizer));

        HeartRateTools::instance()->getLog()->INFO("native started");

    } catch (const std::runtime_error& e) {
        HeartRateTools::instance()->getLog()->ERROR((
                format("runtime error in hrm native start: %1%") % e.what()
                ).str());
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

        boost::tuple<TimeStamp, ElapsedTime> ts =
                TimeCounter::instance()->getTimeStampExt();

        dynamic_cast<NV21FrameSource&>(*nv21).putFrame(
                static_cast<uint16_t>(rows),
                static_cast<uint16_t>(cols),
                reinterpret_cast<uint8_t *>(imageData),
                ts.get<0>()
                );

    } catch (const std::runtime_error& e) {
        hrm::HeartRateTools::instance()->getLog()->ERROR((
                format("put frame error: %1%") % e.what()
        ).str());
    } catch (...) {
        hrm::HeartRateTools::instance()->getLog()->ERROR("fatal error");
    }

    JNIEnv_->ReleaseByteArrayElements(data, imageData, 0);
    return false;
}
