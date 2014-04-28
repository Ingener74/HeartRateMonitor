/*
 * ImageViewFrameDrawer.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: ingener
 */

#include <jni.h>
#include <android/bitmap.h>

#include "ImageViewFrameDrawer.h"

namespace hrm {

#define CHECK(condition, error_message){                                       \
    if(condition)                                                              \
        throw HRDrawException((                                                \
        format("runtime error: %1%") % error_message                           \
        ).str());}

ImageViewFrameDrawer::ImageViewFrameDrawer(
        JNIEnv * jniEnv, jobject object_self, const std::string& methodName) :
        _isError(false), _javaVM(nullptr), _object_global_self(nullptr),
        _method_self_drawBitmap(nullptr) {

    jint res = jniEnv->GetJavaVM(&_javaVM);
    CHECK(res != JNI_OK, "can't get java vm");

    jclass class_self = jniEnv->GetObjectClass(object_self);
    CHECK(!class_self, "can't get self class");

    _object_global_self = jniEnv->NewGlobalRef(object_self);
    CHECK(!_object_global_self, "can't create global ref self class");

    _method_self_drawBitmap = jniEnv->GetMethodID(class_self,
            methodName.c_str(), "(Landroid/graphics/Bitmap;)V");
    CHECK(!_method_self_drawBitmap, "can't get drawBigmap method");

    jniEnv->DeleteLocalRef(class_self);
}

ImageViewFrameDrawer::~ImageViewFrameDrawer() {
}

void ImageViewFrameDrawer::drawFrame(FrameRGB frame) throw (HRDrawException) {
    if (!frame) {
        Log(ERR) << "image is empty";
        return;
    }

    if (_isError) {
        Log(ERR) << "is error";
        return;
    }

    JNIEnv * jniEnv = 0;
    jint res = 0;
    res = _javaVM->AttachCurrentThread(reinterpret_cast<JNIEnv **>(&jniEnv),
    NULL);
    CHECK(res != JNI_OK, "can't attach current thread");

    line(frame, Point(10, 10), Point(10, 100), { 0, 255, 0 });
    line(frame, Point(10, 100), Point(100, 100), { 0, 0, 255 });
    line(frame, Point(100, 100), Point(100, 10), { 255, 0, 0 });
    line(frame, Point(100, 10), Point(10, 10), { 0, 255, 0 });

    circle(frame, Point(50, 50), 30, { 125, 0, 125 });

    jclass class_Bitmap = (jclass) jniEnv->FindClass("android/graphics/Bitmap");
    jmethodID method_Bitmap_createBitmap = jniEnv->GetStaticMethodID(
            class_Bitmap, "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jstring string_Config_Name = jniEnv->NewStringUTF("ARGB_8888");
    CHECK(!string_Config_Name, "can't create config string");

    jclass class_Bitmap_Config = jniEnv->FindClass(
            "android/graphics/Bitmap$Config");
    CHECK(!class_Bitmap, "can't find bitmap config class");

    jobject object_Bitmap_Config = jniEnv->CallStaticObjectMethod(
            class_Bitmap_Config,
            jniEnv->GetStaticMethodID(class_Bitmap_Config, "valueOf",
                    "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;"),
            string_Config_Name);
    CHECK(!object_Bitmap_Config, "can't create bitmap config object");

    jobject object_Bitmap = jniEnv->CallStaticObjectMethod(class_Bitmap,
            method_Bitmap_createBitmap, frame.getFormat().rect._cols,
            frame.getFormat().rect._rows, object_Bitmap_Config);

    uint8_t *data = 0;
    res = AndroidBitmap_lockPixels(jniEnv, object_Bitmap,
            reinterpret_cast<void **>(&data));
    CHECK(res != ANDROID_BITMAP_RESULT_SUCCESS, "can't lock pixels");

    if (data) {

        RGB * src = frame.getData();
        uint8_t *dst = data;
        for (int i = 0, imax = frame.getFormat().rect._rows; i < imax; ++i) {
            for (int j = 0, jmax = frame.getFormat().rect._cols; j < jmax;
                    ++j, ++src) {
                *dst++ = src->r;
                *dst++ = src->g;
                *dst++ = src->b;
                *dst++ = 255;
            }
        }

        res = AndroidBitmap_unlockPixels(jniEnv, object_Bitmap);
        CHECK(res != ANDROID_BITMAP_RESULT_SUCCESS, "can't unlock pixels");
    }

    jniEnv->CallVoidMethod(_object_global_self, _method_self_drawBitmap,
            object_Bitmap);

    /* clean up */
    jniEnv->DeleteLocalRef(class_Bitmap);
    jniEnv->DeleteLocalRef(class_Bitmap_Config);
    jniEnv->DeleteLocalRef(string_Config_Name);
    jniEnv->DeleteLocalRef(object_Bitmap_Config);
    jniEnv->DeleteLocalRef(object_Bitmap);

    CHECK((res = _javaVM->DetachCurrentThread()) != JNI_OK,
            "can't detach current thread");
}

} /* namespace hrm */
