/*
 * Types.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <time.h>

#include <boost/smart_ptr.hpp>

namespace hrm {

class TimeCounter {
public:
    TimeCounter() :
            _time(0), _delta(0) {
    }
    virtual ~TimeCounter() {
    }
    double timeElapsedInMS() {
        struct timespec tm;
        clock_gettime(CLOCK_MONOTONIC, &tm);

        uint64_t t1 = tm.tv_sec * 1000000000LL + tm.tv_nsec;
        double t = double(t1 / 1e6);
        _delta = t - _time;
        _time = t;
        return _delta;
    }

private:
    double _time, _delta;
};

struct FrameRect {
    FrameRect(uint16_t rows = 0, uint16_t cols = 0) :
            _rows(rows), _cols(cols) {
    }
    virtual ~FrameRect() {
    }
    bool operator==(const FrameRect& other) const {
        return (_rows == other._rows && _cols == other._cols);
    }
    bool operator!=(const FrameRect& other) const {
        return (_rows != other._rows || _cols != other._cols);
    }
    bool operator!() const {
        return (!_rows || !_cols);
    }
    operator bool() const {
        return _rows && _cols;
    }
    uint32_t area() const {
        return _rows * _cols;
    }
    uint16_t _rows, _cols;
};

struct FrameFormat {
    FrameFormat(FrameRect rect = FrameRect(), uint16_t bitsPerPixel = 8) :
            _rect(rect), _bitsPerPixel(bitsPerPixel) {
    }
    bool operator==(const FrameFormat& other) const {
        return (_rect == other._rect && _bitsPerPixel == other._bitsPerPixel);
    }
    bool operator!=(const FrameFormat& other) const {
        return (_rect != other._rect || _bitsPerPixel != other._bitsPerPixel);
    }
    bool operator!() const {
        return !_rect;
    }
    operator bool() const {
        return _rect.operator bool();
    }
    uint32_t size() const {
        return _rect.area() * _bitsPerPixel / 8;
    }
    FrameRect _rect;
    uint16_t _bitsPerPixel;
};

class Frame {
public:
    Frame(FrameFormat format = FrameFormat()) :
            _format(format) {
        if (_format) {
            _data = boost::shared_array<uint8_t>(new uint8_t[_format.size()]);
        }
    }
    virtual ~Frame() {
    }
    operator bool() const {
        return bool(_format);
    }
    bool operator!() const {
        return !_format;
    }
    const FrameFormat& getFrameFormat() const {
        return _format;
    }
    uint8_t* getData() {
        return _data.get();
    }

private:
    FrameFormat _format;
    boost::shared_array<uint8_t> _data;
};

}  // namespace hrm

#endif /* TYPES_H_ */
