/*
 * ImageViewHeartRateVisualizer.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#include <android/bitmap.h>

#include <heartratemonitor/HeartRateTools.h>

#include "ImageViewHeartRateVisualizer.h"

namespace hrm {

#define CHECK(condition, error_message){ if(_isError)return; if (condition) { \
    HeartRateTools::instance()->getLog()->ERROR(error_message); \
    _isError = true; return;} }

ImageViewHeartRateVisualizer::ImageViewHeartRateVisualizer(JNIEnv * jniEnv,
        jobject object_self) :
        _isError(false),
        _javaVM(0),
        _object_self(0),
        _class_self(0),
        _method_self_drawBitmap(0),
        _field_ImageView(0),
        _object_ImageView(0) {

    jint res = jniEnv->GetJavaVM(&_javaVM);
    CHECK(res != JNI_OK, "can't get java vm");

    _class_self = jniEnv->FindClass(
            "com/shnayder/heartratemonitor/HeartRateMonitorPreview");
    CHECK(!_class_self, "can't find self class");

    _object_self= jniEnv->NewGlobalRef(object_self);
    CHECK(!_object_self, "can't create global ref self class");

    _method_self_drawBitmap = jniEnv->GetMethodID(
            _class_self, "drawBitmap", "(Landroid/graphics/Bitmap;)V");
    CHECK(!_method_self_drawBitmap, "can't get drawBigmap method");

    _field_ImageView = jniEnv->GetFieldID(_class_self, "_imageView", "Landroid/widget/ImageView;");
    CHECK(!_field_ImageView, "can't get image view field id");

    _object_ImageView = jniEnv->GetObjectField(object_self, _field_ImageView);
    CHECK(!_object_ImageView, "can't get image view object field");
}

ImageViewHeartRateVisualizer::~ImageViewHeartRateVisualizer() {
    /* todo attach current thread and delete global ref */
}

void ImageViewHeartRateVisualizer::visualizeHeartRate(
        MeasurementGraph heartRateMeasuredGraph) {

    if(_isError){
        HeartRateTools::instance()->getLog()->ERROR("is error");
        return;
    }

    JNIEnv * jniEnv = 0;
    jint res = 0;
    res = _javaVM->AttachCurrentThread(reinterpret_cast<JNIEnv **>(&jniEnv),
            NULL);
    CHECK(res != JNI_OK, "can't attach current thread");

    int32_t rows = 480, cols = 640;
    RGBImage testImage = RGBImage(ImageFormatRGB(ImageRect(rows, cols)));

    RGB * dst = testImage.getData();
    for (int i = 0, imax = testImage.getFormat().rect._rows; i < imax; ++i) {
        for (int j = 0, jmax = testImage.getFormat().rect._cols; j < jmax; ++j, dst += 3) {
            if(i >= rows / 2 || j >= rows / 2)
                continue;
            dst->r = i % 255;
            dst->g = j % 255;
            dst->b = 0;
        }
    }

    jclass class_Bitmap = (jclass)jniEnv->FindClass("android/graphics/Bitmap");
    jmethodID method_Bitmap_createBitmap = jniEnv->GetStaticMethodID(
            class_Bitmap,
            "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jstring string_Config_Name = jniEnv->NewStringUTF("ARGB_8888");
    CHECK(!string_Config_Name, "can't create config string");

    jclass class_Bitmap_Config = jniEnv->FindClass(
            "android/graphics/Bitmap$Config");
    CHECK(!class_Bitmap, "can't find bitmap config class");

    jobject object_Bitmap_Config = jniEnv->CallStaticObjectMethod(
            class_Bitmap_Config,
            jniEnv->GetStaticMethodID(
                    class_Bitmap_Config,
                    "valueOf",
                    "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;"),
                    string_Config_Name);
    CHECK(!object_Bitmap_Config, "can't create bitmap config object");

    jobject object_Bitmap = jniEnv->CallStaticObjectMethod(
            class_Bitmap,
            method_Bitmap_createBitmap,
            cols, rows,
            object_Bitmap_Config);

    uint8_t *data = 0;
    res = AndroidBitmap_lockPixels(jniEnv, object_Bitmap, reinterpret_cast<void **>(&data));
    CHECK(res != ANDROID_BITMAP_RESULT_SUCCESS, "can't lock pixels");

    if(data){

        RGB * src = testImage.getData();
        uint8_t *dst = data;
        for (int i = 0, imax = rows; i < imax; ++i) {
            for (int j = 0, jmax = cols; j < jmax; ++j, ++src) {
                *dst++ = src->r;
                *dst++ = src->g;
                *dst++ = src->b;
                *dst++ = 255;
            }
        }

        res = AndroidBitmap_unlockPixels(jniEnv, object_Bitmap);
        CHECK(res != ANDROID_BITMAP_RESULT_SUCCESS, "can't unlock pixels");
    }

    jniEnv->CallVoidMethod(_object_self, _method_self_drawBitmap, object_Bitmap);

    /* clean up */
    jniEnv->DeleteLocalRef(class_Bitmap);
    jniEnv->DeleteLocalRef(class_Bitmap_Config);
    jniEnv->DeleteLocalRef(string_Config_Name);
    jniEnv->DeleteLocalRef(object_Bitmap_Config);
    jniEnv->DeleteLocalRef(object_Bitmap);

    CHECK((res = _javaVM->DetachCurrentThread()) != JNI_OK,
            "can't detach current thread");
}

}  // namespace hrm

