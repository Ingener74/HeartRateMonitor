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

#include <memory>
#include <tuple>
#include <thread>
#include <mutex>
#include <vector>

#include <boost/thread.hpp>

namespace hrm {

typedef double TimeStamp;
typedef double ElapsedTime;

typedef int32_t NormalizedMeasurementValue;
typedef int32_t HeartRateValue;

typedef int64_t HeartBeatID;

typedef std::tuple<TimeStamp, NormalizedMeasurementValue>
    RawMeasurement;
typedef std::tuple<TimeStamp, NormalizedMeasurementValue, HeartBeatID>
    Measurement;

typedef std::vector<RawMeasurement> RawMeasurementGraph;
typedef std::vector<Measurement> MeasurementGraph;

class TimeCounter {
public:
    static TimeCounter * instance();
    virtual ~TimeCounter();

    TimeStamp getTimeStamp();
    std::tuple<TimeStamp, ElapsedTime> getTimeStampExt();

private:
    TimeCounter();
    TimeStamp _time;
};

struct RGB{ uint8_t r, g, b; };
struct RGBA{ uint8_t r, g, b, a; };
struct BGR{ uint8_t b, g, r; };
struct BGRA{ uint8_t b, g, r, a; };

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

typedef TypeImageFormat<RGB> ImageFormatRGB;
typedef TypeImageFormat<RGBA> ImageFormatRGBA;
typedef TypeImageFormat<BGR> ImageFormatBGR;
typedef TypeImageFormat<BGRA> ImageFormatBGRA;

struct BitsPerPixelImageFormat {
    typedef uint8_t PixelType;
    BitsPerPixelImageFormat(
            ImageRect rect = ImageRect(), uint32_t bitsPerPixel = 8):
            rect(rect), bitsPerPixel(bitsPerPixel){
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
        return rect.area() * bitsPerPixel / 8;
    }
    uint32_t bitsPerPixel;
    ImageRect rect;
};

//struct ImageFormat {
//    ImageFormat(ImageRect rect = ImageRect()): _rect(rect){}
//
//    virtual bool operator==(const ImageFormat& other) const ;
//    virtual bool operator!=(const ImageFormat& other) const ;
//    virtual uint32_t size() const = 0;
//
//    bool operator!() const ;
//    operator bool() const ;
//
//    ImageRect _rect;
//};

template <typename ImageFormat>
class Image;

template <typename ImageFormat>
class ImageData{
public:
    typedef std::shared_ptr<ImageData<ImageFormat> > Ptr;
    typedef std::shared_ptr<typename ImageFormat::PixelType> Array;

    ImageFormat _format;
    Array _data;

    ImageData(ImageFormat if_):
        _format(if_),
        _data(new typename ImageFormat::PixelType[if_.size()],
                [](typename ImageFormat::PixelType * p){delete []p;}) {}

};

template<typename ImageFormat>
class Image{
protected:
    typename ImageData<ImageFormat>::Ptr _p;

public:
    Image(ImageFormat format = ImageFormat()):
        _p(new ImageData<ImageFormat>(format)){
    }
    virtual ~Image(){}
    operator bool() const {
        return _p->_format;
    }
    bool operator!() const {
        return !_p->_format;
    }
//    void operator << (const Image& original){
//        _format = original._format;
//        _data = boost::shared_array<uint8_t>(new uint8_t[_format.size()]);
//        uint8_t * src = original._data.get(), * dst = _data.get();
//        for (int i = 0, imax = _format.size(); i < imax; ++i) {
//            *dst++ = *src++;
//        }
//    }
    const ImageFormat& getFormat() const {
        return _p->_format;
    }
    typename ImageFormat::PixelType* getData() {
        return _p->_data.get();
    }

//    enum DrawLineMethod {
//        DrawLineMethod_DDA,
//        DrawLineMethod_Bresenham,
//        DrawLineMethod_By,
//    };
//    static void drawLine(Image image, const Point& p1,
//            const Point& p2 = Point(),
//            const Color& color = Color(),
//            DrawLineMethod method = DrawLineMethod_DDA);
};

typedef Image<ImageFormatRGB> RGBImage;
typedef Image<ImageFormatRGBA> RGBAImage;
typedef Image<ImageFormatBGR> BGRImage;
typedef Image<ImageFormatBGRA> BGRAImage;

template<typename ImageFormat>
class Frame: public Image<ImageFormat> {
public:
    Frame(ImageFormat format = ImageFormat(), TimeStamp timeStamp = 0.0) :
            Image<ImageFormat>(format), _timeStamp(timeStamp) {
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

typedef Frame<TypeImageFormat<RGB> > FrameRGB;
typedef Frame<TypeImageFormat<RGBA> > FrameRGBA;
typedef Frame<TypeImageFormat<BGR> > FrameBGR;
typedef Frame<TypeImageFormat<BGRA> > FrameBGRA;

template <typename ImageFormat>
struct LockedFrame{
    typedef std::tuple<
            std::shared_ptr<boost::unique_lock<boost::shared_mutex> >,
            Frame<ImageFormat> > Unique;

    typedef std::tuple<
            std::shared_ptr<boost::shared_lock<boost::shared_mutex> >,
            Frame<ImageFormat> > Shared;
};

typedef LockedFrame<TypeImageFormat<RGB> >::Shared FrameSharedLockedRGB;
typedef LockedFrame<TypeImageFormat<RGBA> >::Shared FrameSharedLockedRGBA;
typedef LockedFrame<TypeImageFormat<BGR> >::Shared FrameSharedLockedBGR;
typedef LockedFrame<TypeImageFormat<BGRA> >::Shared FrameSharedLockedBGRA;

}  // namespace hrm

#endif /* TYPES_H_ */
