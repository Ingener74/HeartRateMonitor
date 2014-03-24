/*
 * ImageViewImageDrawer.h
 *
 *  Created on: 23 февр. 2014 г.
 *      Author: ingener
 */

#ifndef IMAGEVIEWIMAGEDRAWER_H_
#define IMAGEVIEWIMAGEDRAWER_H_

#include <jni.h>

#include "IRGBImageDrawer.h"

namespace hrm {

class ImageViewImageDrawer: public IRGBImageDrawer {
public:
    ImageViewImageDrawer(JNIEnv * jniEnv, jobject object_self);
    virtual ~ImageViewImageDrawer();

    virtual void drawImage(RGBImage image);

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

#endif /* IMAGEVIEWIMAGEDRAWER_H_ */
