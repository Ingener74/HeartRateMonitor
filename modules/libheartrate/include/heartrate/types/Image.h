/*
 * Image.h
 *
 *  Created on: Apr 14, 2014
 *      Author: pavel
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include <heartrate/HeartRateCommon.h>

namespace hrm {

template<typename TDataType>
using ImageData = shared_ptr<TDataType[]>;

using Rows          = uint16_t;
using Cols          = uint16_t;
using Area          = uint32_t;
using Size          = uint32_t;
using TimeStamp     = uint64_t;
using Data          = void *;
using BitsPerPixel  = uint16_t;

enum class ImageType {
    RGB,
    BGR,
    RGBA,
    BGRA,

    NV21,
};

const static BitsPerPixel bitsPerPixels[] = {
        24, /* RGB  */
        24, /* BGR  */
        32, /* RGBA */
        32, /* BGRA */

        12, /* NV21 */
};

class ImageRect {
public:
    ImageRect(Rows rows, Cols cols) :
            _rows(rows), _cols(cols) {
    }
    virtual ~ImageRect(){
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

    Area getArea() const {
        return _rows * _cols;
    }

    Rows _rows;
    Cols _cols;
};

class ImageFormat {
public:
    ImageFormat(const ImageRect& rect, ImageType type = ImageType::RGB) :
            _rect(rect), _imageType(type) {
    }
    virtual ~ ImageFormat() {
    }

    Size getSize() const {
        return _rect.getArea() * getBitsPerPixel(_imageType) / 8;
    }

    ImageRect _rect;
    ImageType _imageType;

    static BitsPerPixel getBitsPerPixel(ImageType imageType) {
        return bitsPerPixels[imageType];
    }
};

class Image {
public:
    Image(ImageFormat) {
    }
    virtual ~Image() {
    }

    void lock() {
        _imageMutex.lock();
    }

    void unlock() {
        _imageMutex.unlock();
    }

    mutex& getImageMutex() const {
        return _imageMutex;
    }

private:
    friend class ImageLock;

    mutex _imageMutex;

    ImageData<uint8_t> _data;
    ImageFormat _format;
};

class ImageLock {
public:
    ImageLock(Image& image) :
            _image(image) {
        _image.lock();
    }
    virtual ~ImageLock() {
        _image.unlock();
    }

    ImageFormat getImageFormat() const {
        return _image._format;
    }
    template<typename TData>
    TData getData() const {
        return static_cast<TData*>(_image._data.get());
    }

private:
    Image& _image;
};

class Frame: public Image {
public:
    TimeStamp _timeStamp;
};

}  // namespace hrm

#endif /* IMAGE_H_ */
