/*
 * ImageViewHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IMAGEVIEWHEARTRATEVISUALIZER_H_
#define IMAGEVIEWHEARTRATEVISUALIZER_H_

#include <jni.h>

#include "IHeartRateVisualizer.h"

namespace hrm {

class ImageViewHeartRateVisualizer: public IHeartRateVisualizer {
public:
    ImageViewHeartRateVisualizer(JNIEnv * jniEnv, jobject object_self);
    virtual ~ImageViewHeartRateVisualizer();

    virtual void visualizeHeartRate(MeasurementGraph heartRateMeasuredGraph);

private:
    bool _isError;

    JavaVM * _javaVM;
    jobject _object_self;
    jclass _class_self;
    jmethodID _method_self_drawBitmap;

    jfieldID _field_ImageView;
    jobject _object_ImageView;
};

}  // namespace hrm

#endif /* IMAGEVIEWHEARTRATEVISUALIZER_H_ */
