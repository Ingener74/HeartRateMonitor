/*
 * ImageViewFrameDrawer.h
 *
 *  Created on: Apr 5, 2014
 *      Author: ingener
 */

#ifndef IMAGEVIEWFRAMEDRAWER_H_
#define IMAGEVIEWFRAMEDRAWER_H_

#include <heartratemonitor/IRGBFrameDrawer.h>

namespace hrm {

class ImageViewFrameDrawer: public IRGBFrameDrawer {
public:
    ImageViewFrameDrawer(JNIEnv * jniEnv, jobject object_self);
    virtual ~ImageViewFrameDrawer();

    virtual void drawFrame(FrameRGB frame) throw (DrawError);
private:
    JavaVM * _javaVM;
    jobject _object_self;
    jclass _class_self;
    jmethodID _method_self_drawBitmap;

    jfieldID _field_ImageView;
    jobject _object_ImageView;
};

} /* namespace hrm */

#endif /* IMAGEVIEWFRAMEDRAWER_H_ */
