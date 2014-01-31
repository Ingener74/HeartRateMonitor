/*
 * Types.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

#include <boost/tuple/tuple.hpp>
#include <boost/smart_ptr.hpp>

namespace hrm {

typedef double TimeStamp;
typedef double ElapsedTime;
//typedef boost::tuple<TimeStamp, ElapsedTime>

class TimeCounter {
public:
    static TimeCounter * instance();
    virtual ~TimeCounter();

    TimeStamp getTimeStamp();
    boost::tuple<TimeStamp, ElapsedTime> getTimeStampExt();

private:
    TimeCounter();
    TimeStamp _time;
};

struct ImageRect {
    ImageRect(uint16_t rows = 0, uint16_t cols = 0) :
            _rows(rows), _cols(cols) {
    }
    virtual ~ImageRect() {
    }
    bool operator==(const ImageRect& other) const {
        return (_rows == other._rows && _cols == other._cols);
    }
    bool operator!=(const ImageRect& other) const {
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

struct ImageFormat {
    ImageFormat(ImageRect rect = ImageRect(), uint16_t bitsPerPixel = 8) :
            _rect(rect), _bitsPerPixel(bitsPerPixel) {
    }
    bool operator==(const ImageFormat& other) const {
        return (_rect == other._rect && _bitsPerPixel == other._bitsPerPixel);
    }
    bool operator!=(const ImageFormat& other) const {
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
    ImageRect _rect;
    uint16_t _bitsPerPixel;
};

class Image{
public:
    Image(ImageFormat format = ImageFormat()) :
            _format(format) {
        if (_format)
            _data = boost::shared_array<uint8_t>(new uint8_t[_format.size()]);
    }
    virtual ~Image(){}
    operator bool() const {
        return bool(_format);
    }
    bool operator!() const {
        return !_format;
    }
    void operator << (const Image& original){
        _format = original._format;
        _data = boost::shared_array<uint8_t>(new uint8_t[_format.size()]);
        uint8_t * src = original._data.get(), * dst = _data.get();
        for (int i = 0, imax = _format.size(); i < imax; ++i) {
            *dst++ = *src++;
        }
    }
    const ImageFormat& getFormat() const {
        return _format;
    }
    uint8_t* getData() {
        return _data.get();
    }
protected:
    ImageFormat _format;
    boost::shared_array<uint8_t> _data;
};

class Frame: public Image {
public:
    Frame(ImageFormat format = ImageFormat(), TimeStamp timeStamp = 0.0) :
            Image(format), _timeStamp(timeStamp) {
    }
    virtual ~Frame() {
    }
    void setTimeStamp(TimeStamp timeStamp) {
        _timeStamp = timeStamp;
    }
    const TimeStamp getTimeStamp() const {
        return _timeStamp;
    }

private:
    TimeStamp _timeStamp;
};

}  // namespace hrm

#endif /* TYPES_H_ */
