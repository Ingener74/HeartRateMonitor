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
    ImageViewFrameDrawer(JNIEnv * jniEnv, jobject object_self, const std::string& methodName);
    virtual ~ImageViewFrameDrawer();

    virtual void drawFrame(FrameRGB frame) throw (DrawError);
private:
    bool _isError;

    JavaVM * _javaVM;
    jobject _object_global_self;
    jmethodID _method_self_drawBitmap;
};

} /* namespace hrm */

#endif /* IMAGEVIEWFRAMEDRAWER_H_ */
