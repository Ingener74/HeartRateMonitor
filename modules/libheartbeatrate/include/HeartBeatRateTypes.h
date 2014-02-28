/*
 * Types.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <cmath>

#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/smart_ptr.hpp>

namespace hrm {

typedef double TimeStamp;
typedef double ElapsedTime;

typedef int32_t NormalizedMeasurementValue;
typedef int32_t HeartRateValue;

typedef int64_t HeartBeatID;

typedef boost::tuple<TimeStamp, NormalizedMeasurementValue>
    RawMeasurement;
typedef boost::tuple<TimeStamp, NormalizedMeasurementValue, HeartBeatID>
    Measurement;

typedef std::vector<RawMeasurement> RawMeasurementGraph;
typedef std::vector<Measurement> MeasurementGraph;

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

struct Point{
    Point(int32_t x = 0, int32_t y = 0): x(x), y(y){
    }
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
    bool operator!=(const Point& other) const {
        return (x != other.x || y != other.y);
    }
    static double distance(const Point& p1, const Point &p2){
        return sqrt((p2.y - p1.y)*(p2.y - p1.y) + (p2.x - p1.x)*(p2.x - p1.x));
    }
    int32_t x, y;
};

struct Color{
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0):
        r(r), g(g), b(b), a(a){
    }
    uint8_t r, g, b, a;
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

template <typename imageType>
struct TypeImageFormat {
    typedef imageType PixelType;
    TypeImageFormat(ImageRect rect = ImageRect()): rect(rect){
    }
    bool operator!() const {
        return !rect;
    }
    operator bool() const {
        return rect.operator bool();
    }
    bool operator==(const TypeImageFormat& other) const {
        return false;
    }
    bool operator!=(const TypeImageFormat& other) const {
        return false;
    }
    uint32_t size() const {
        return rect.area() * sizeof(imageType);
    }
    ImageRect rect;
};

struct BitsPerPixelImageFormat {
    typedef uint8_t PixelType;
    BitsPerPixelImageFormat(
            ImageRect rect = ImageRect(), uint32_t bitsPerPixel = 8):
            rect(rect), _bitsPerPixel(bitsPerPixel){
    }
    bool operator!() const {
        return !rect;
    }
    operator bool() const {
        return rect.operator bool();
    }
    bool operator==(const BitsPerPixelImageFormat & other) const {
        return false;
    }
    bool operator!=(const BitsPerPixelImageFormat & other) const {
        return false;
    }
    uint32_t size() const {
        return rect.area() * _bitsPerPixel / 8;
    }
    uint32_t _bitsPerPixel;
    ImageRect rect;
};

//struct ImageFormat {
//    ImageFormat(ImageRect rect = ImageRect()): _rect(rect){}
//
//    virtual bool operator==(const ImageFormat& other) const = 0;
//    virtual bool operator!=(const ImageFormat& other) const = 0;
//    virtual uint32_t size() const = 0;
//
//    bool operator!() const ;
//    operator bool() const ;
//
//    ImageRect _rect;
//};

template<typename ImageFormat>
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
    ImageFormat::PixelType* getData() {
        return _data.get();
    }

    enum DrawLineMethod {
        DrawLineMethod_DDA,
        DrawLineMethod_Bresenham,
        DrawLineMethod_By,
    };
    static void drawLine(Image image, const Point& p1,
            const Point& p2 = Point(),
            const Color& color = Color(),
            DrawLineMethod method = DrawLineMethod_DDA);

protected:
    class ImageData;
    boost::shared_ptr<ImageData> _p;

};

class Image::ImageData{
public:
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
