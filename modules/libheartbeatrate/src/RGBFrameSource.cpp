/*
 * RGBFrameSource.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#include <algorithm>
#include <boost/format.hpp>

#include "HeartRateTools.h"
#include "RGBFrameSource.h"
#include "HeartBeatRateDefines.h"

namespace hrm {

RGBFrameSource::RGBFrameSource(INV21FrameSource::Ptr nv21) :
        _nv21(nv21) {
}

RGBFrameSource::~RGBFrameSource() {
}

FrameSharedLockedRGB RGBFrameSource::getFrame(){
    {
        LockedFrame<BitsPerPixelImageFormat>::Shared lockedFrame = _nv21->getFrame();

        boost::unique_lock<boost::shared_mutex> lock(_frameMutex);

        ImageRect r = lockedFrame.get<1>().getFormat().rect;
        if(_frame.getFormat().rect != r){
            _frame = FrameRGB(ImageFormatRGB(r));
//            HeartRateTools::instance()->getLog()->DEBUG((boost::format(
//                    "rgb frame resized %1% x %2%")
//            % _frame.getFormat()._rect._rows
//            % _frame.getFormat()._rect._cols).str());
        }
        /* Internet sources
         *
         * http://ru.wikipedia.org/wiki/YUV
         * http://linuxtv.org/downloads/v4l-dvb-apis/re29.html
         * http://stackoverflow.com/questions/5272388/extract-black-and-white-image-from-android-cameras-nv21-format
         * http://www.fourcc.org/fccyvrgb.php
         *
         * Convert nv21 to rgb
         *
         *   Y1   Y2   Y3   Y4   Y5   Y6
         *   Y7   Y8   Y9   Y10  Y11  Y12
         *   Y13  Y14  Y15  Y16  Y17  Y18
         *   Y19  Y20  Y21  Y22  Y23  Y24
         *   U1   V1   U2   V2   U3   V3
         *   U4   V4   U5   V5   U6   V6
         *
         * Byte stream
         *
         *   Y1   Y2   Y3   Y4   Y5   Y6   Y7   Y8   Y9   Y10  Y11  Y12   Y13  Y14  Y15  Y16  Y17  Y18   Y19  Y20  Y21  Y22  Y23  Y24 ....
         *      U1   V1   U2   V2   U3   V3   U4   V4   U5   V5   U6   V6
         */
        uint8_t * y = lockedFrame.get<1>().getData();
        uint8_t * uv = y + lockedFrame.get<1>().getFormat().rect.area();

        RGB * rgb = _frame.getData();

        for (uint32_t i = 0, imax = _frame.getFormat().rect._rows; i < imax; i += 2){

            for (uint32_t j = 0, jmax = _frame.getFormat().rect._cols; j < jmax; j += 2){

                int Y1 = int(*(y +  i     *jmax +  j      )) - 16;
                int Y2 = int(*(y +  i     *jmax + (j + 1) )) - 16;
                int Y3 = int(*(y + (i + 1)*jmax +  j      )) - 16;
                int Y4 = int(*(y + (i + 1)*jmax + (j + 1) )) - 16;

                int U = int(*uv++) - 128;
                int V = int(*uv++) - 128;

                RGB* rgb1 = rgb +  i     *jmax +  j      ;
                RGB* rgb2 = rgb +  i     *jmax + (j + 1) ;
                RGB* rgb3 = rgb + (i + 1)*jmax +  j      ;
                RGB* rgb4 = rgb + (i + 1)*jmax + (j + 1) ;

#define YUV2RGB(Y, U, V, pRGB){                             \
                int r = 1.164 * Y              + 2.018 * U; \
                int g = 1.164 * Y -  0.813 * V - 0.391 * U; \
                int b = 1.164 * Y +  1.596 * V;             \
                pRGB->r = std::max(0, std::min(r, 255));    \
                pRGB->g = std::max(0, std::min(g, 255));    \
                pRGB->b = std::max(0, std::min(b, 255));}   \

                YUV2RGB(Y1, U, V, rgb1);
                YUV2RGB(Y2, U, V, rgb2);
                YUV2RGB(Y3, U, V, rgb3);
                YUV2RGB(Y4, U, V, rgb4);
            }
        }
        _frame.setTimeStamp(lockedFrame.get<1>().getTimeStamp());
//        HeartRateTools::instance()->getLog()->DEBUG("rgb frame converted");
    }
    FrameSharedLockedRGB lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)), _frame);
    return lockedFrame;
}

}  // namespace hrm

