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

        FrameRect r = lockedFrame.get<1>().getFrameFormat()._rect;
        if(_frame.getFrameFormat()._rect != r){
            _frame = Frame(FrameFormat(r, 3));
            D("rgb frame resized %d x %d", _frame.getFrameFormat()._rect._rows, _frame.getFrameFormat()._rect._cols);
        }
        /*
         * convert nv21 to rgb
         */
        uint8_t * y = lockedFrame.get<1>().getData();
        uint8_t * uv = y + lockedFrame.get<1>().getFrameFormat()._rect.area();

        uint8_t * rgb = _frame.getData();
        for (int i = 0, imax = _frame.getFrameFormat()._rect.area();
                i < imax;
                ++i, rgb += 3, ++y, uv += 2) {

            uint8_t Y = *y;
            uint8_t U = *uv;
            uint8_t V = *(uv + 1);

            uint8_t r = Y + 1.13983 * (V - 128);
            uint8_t g = Y - 0.39465 * (U - 128) - 0.58060 * (V - 128);
            uint8_t b = Y + 2.03211 * (U - 128);

            r = std::max(uint8_t(0), std::min(r, uint8_t(255)));
            g = std::max(uint8_t(0), std::min(g, uint8_t(255)));
            b = std::max(uint8_t(0), std::min(b, uint8_t(255)));
        }
        D("rgb frame converted");
    }
    SharedLockedFrame lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)), _frame);
    return lockedFrame;
}

}  // namespace hrm

