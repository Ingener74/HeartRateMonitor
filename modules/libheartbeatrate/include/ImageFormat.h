/*
 * ImageFormat.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef IMAGEFORMAT_H_
#define IMAGEFORMAT_H_

namespace hrm {

class ImageFormat {
public:
    enum {
        UNKNOWN = 0,
        RGB_565 = 4,
        NV16 = 16,
        NV21 = 17,
        YUY2 = 20,
        YUV_420_888 = 35,
        JPEG = 256,
        YV12 = 842094169
    };
    static ImageFormat* instance() {
        static boost::scoped_ptr<ImageFormat> ptr(new ImageFormat());
        return ptr.get();
    }
    std::string getImageFormatString(int imageFormat) {
        try {
            std::string res = _imageFormatTranslations[imageFormat];
            return res;
        } catch (...) {
            return std::string("");
        }
    }
    virtual ~ImageFormat() {
    }

private:
    ImageFormat() {
        _imageFormatTranslations[UNKNOWN] = "UNKNOWN";
        _imageFormatTranslations[RGB_565] = "RGB_565";
        _imageFormatTranslations[NV16] = "NV16";
        _imageFormatTranslations[NV21] = "NV21";
        _imageFormatTranslations[YUY2] = "YUY2";
        _imageFormatTranslations[YUV_420_888] = "YUV_420_888";
        _imageFormatTranslations[JPEG] = "JPEG";
        _imageFormatTranslations[YV12] = "YV12";
    }

    std::map<int, std::string> _imageFormatTranslations;
};

}  // namespace hrm

#endif /* IMAGEFORMAT_H_ */
