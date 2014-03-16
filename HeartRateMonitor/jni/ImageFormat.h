/*
 * ImageFormat.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef IMAGEFORMAT_H_
#define IMAGEFORMAT_H_

#include <string>
#include <memory>
#include <map>
#include <boost/assign/list_of.hpp>

namespace hrm {

class AndroidImageFormat {
public:
    enum Type{
        UNKNOWN = 0,
        RGB_565 = 4,
        NV16 = 16,
        NV21 = 17,
        YUY2 = 20,
        YUV_420_888 = 35,
        JPEG = 256,
        YV12 = 842094169
    };
    static AndroidImageFormat& instance() {
        static std::unique_ptr<AndroidImageFormat> ptr(
                new AndroidImageFormat());
        return *ptr;
    }
    std::string getImageFormatString(Type imageFormat) {
        std::string res = _imageFormatTranslations[imageFormat];
        if (res.empty())
            return "Unknown image format";
        return res;
    }
    virtual ~AndroidImageFormat() {
    }

private:
    AndroidImageFormat() {
        std::map<Type, std::string> t = boost::assign::map_list_of
                (UNKNOWN, "UNKNOWN")
                (RGB_565, "RGB_565")
                (NV16, "NV16")
                (NV21, "NV21")
                (YUY2, "YUY2")
                (YUV_420_888, "YUV_420_888")
                (JPEG, "JPEG")
                (YV12, "YV12");
        _imageFormatTranslations = t;
    }

    std::map<Type, std::string> _imageFormatTranslations;
};

}  // namespace hrm

#endif /* IMAGEFORMAT_H_ */
