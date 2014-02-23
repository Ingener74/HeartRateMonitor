/*
 * ImageViewImageDrawer.h
 *
 *  Created on: 23 февр. 2014 г.
 *      Author: ingener
 */

#ifndef IMAGEVIEWIMAGEDRAWER_H_
#define IMAGEVIEWIMAGEDRAWER_H_

#include <jni.h>

#include "IImageDrawer.h"

namespace hrm {

class ImageViewImageDrawer: public IImageDrawer {
public:
    ImageViewImageDrawer(JNIEnv * jniEnv, jobject object_self);
    virtual ~ImageViewImageDrawer();

    virtual void drawImage(Image image);

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
