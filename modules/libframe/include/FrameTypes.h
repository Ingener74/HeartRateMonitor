
#ifndef FRAMETYPES_H_
#define FRAMETYPES_H_

#include <stdint.h>

#include <boost/smart_ptr.hpp>

namespace frame {

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
    bool operator bool(){
        return _rows && _cols;
    }
    uint32_t area() const {
        return _rows * _cols;
    }
    uint16_t _rows, _cols;
};
struct FrameFormat {
    FrameFormat(FrameRect rect = FrameRect(), uint16_t bytesInPixel = 1) :
            _rect(rect), _bytesInPixel(bytesInPixel) {
    }
    bool operator==(const FrameFormat& other) const {
        return (_rect == other._rect && _bytesInPixel == other._bytesInPixel);
    }
    bool operator!=(const FrameFormat& other) const {
        return (_rect != other._rect || _bytesInPixel != other._bytesInPixel);
    }
    bool operator!() const {
        return !_rect;
    }
    bool operator bool() const {
        return _rect;
    }
    uint32_t size() const {
        return _rect.area() * _bytesInPixel;
    }
    FrameRect _rect;
    uint16_t _bytesInPixel;
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
    Frame(const Frame& frame) {
    }
    Frame& operator=(const Frame& frame) {
        return *this;
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

} /* namespace frame */

#endif
