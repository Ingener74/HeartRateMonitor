/*
 * RGBFrameSource.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: pavel
 */

#include <algorithm>

#include "RGBFrameSource.h"

#include "HeartBeatRateDefines.h"

namespace hrm {

hrm::RGBFrameSource::RGBFrameSource(boost::shared_ptr<NV21FrameSource> nv21) :
        _nv21(nv21) {
}

hrm::RGBFrameSource::~RGBFrameSource() {
}

SharedLockedFrame RGBFrameSource::getFrame() {
    {
        SharedLockedFrame lockedFrame = _nv21->getFrame();

        boost::unique_lock<boost::shared_mutex> lock(_frameMutex);

        ImageRect r = lockedFrame.get<1>().getFormat()._rect;
        if(_frame.getFormat()._rect != r){
            _frame = Frame(ImageFormat(r, 8 * 3));
            D("rgb frame resized %d x %d", _frame.getFormat()._rect._rows, _frame.getFormat()._rect._cols);
        }
        /*
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
        uint8_t * uv = y + lockedFrame.get<1>().getFormat()._rect.area();

        uint8_t * rgb = _frame.getData();

        uint32_t imax = _frame.getFormat()._rect._rows,
                 jmax = _frame.getFormat()._rect._cols;

        for (uint32_t i = 0; i < imax;    ++i, uv -= jmax) {

            for (uint32_t j = 0; j < jmax;    ++j, rgb += 3, ++y /*, uv += 2*/ ) {

                uint8_t Y = *y;
                uint8_t U = *uv;
                uint8_t V = *(uv + 1);

                uint8_t r = Y + 1.13983 * (V - 128);
                uint8_t g = Y - 0.39465 * (U - 128) - 0.58060 * (V - 128);
                uint8_t b = Y + 2.03211 * (U - 128);

                r = std::max(uint8_t(0), std::min(r, uint8_t(255)));
                g = std::max(uint8_t(0), std::min(g, uint8_t(255)));
                b = std::max(uint8_t(0), std::min(b, uint8_t(255)));

                uv += j%2 * 2;
            }
        }
        _frame.setTimeStamp(lockedFrame.get<1>().getTimeStamp());
        D("rgb frame converted");
    }
    SharedLockedFrame lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)), _frame);
    return lockedFrame;
}

}  // namespace hrm

