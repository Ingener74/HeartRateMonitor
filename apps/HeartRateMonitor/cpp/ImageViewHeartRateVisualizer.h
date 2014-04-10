/*
 * ImageViewHeartRateVisualizer.h
 *
 *  Created on: Feb 19, 2014
 *      Author: pavel
 */

#ifndef IMAGEVIEWHEARTRATEVISUALIZER_H_
#define IMAGEVIEWHEARTRATEVISUALIZER_H_

#include <jni.h>

#include <heartratemonitor/IHeartRateVisualizer.h>

namespace hrm {

class ImageViewHeartRateVisualizer: public IHeartRateVisualizer {
public:
    ImageViewHeartRateVisualizer(JNIEnv * jniEnv, jobject object_self,
            const std::string& methodName);
    virtual ~ImageViewHeartRateVisualizer();

    virtual void visualizeHeartRate(MeasurementGraph heartRateMeasuredGraph);

private:
    bool _isError;

    JavaVM * _javaVM;
    jobject _object_global_self;
    jmethodID _method_self_drawBitmap;
};

}  // namespace hrm

#endif /* IMAGEVIEWHEARTRATEVISUALIZER_H_ */
