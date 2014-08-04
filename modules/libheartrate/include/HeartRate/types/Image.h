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

class ImageRect
{
public:
    ImageRect(Rows rows, Cols cols) :
            _rows(rows), _cols(cols)
    {
    }
    virtual ~ImageRect()
    {
    }
    bool operator==(const ImageRect& other) const
    {
        return (_rows == other._rows && _cols == other._cols);
    }
    bool operator!=(const ImageRect& other) const
    {
        return (_rows != other._rows || _cols != other._cols);
    }
    bool operator!() const
    {
        return (!_rows || !_cols);
    }
    operator bool() const
    {
        return _rows && _cols;
    }
    Area getArea() const
    {
        return _rows * _cols;
    }

    Rows _rows;
    Cols _cols;
};

class ImageFormat
{
public:
    ImageFormat(const ImageRect& rect, ImageType type = ImageType::RGB) :
            _rect(rect), _imageType(type)
    {
    }
    virtual ~ ImageFormat()
    {
    }
    bool operator==(const ImageFormat& other) const
    {
        return (_rect == other._rect && _imageType == other._imageType);
    }
    bool operator!=(const ImageFormat& other) const
    {
        return (_rect != other._rect || _imageType != other._imageType);
    }
    bool operator!() const
    {
        return (!_rect);
    }
    operator bool() const
    {
        return _rect;
    }
    const ImageRect& getRect() const
    {
        return _rect;
    }
    ImageType getImageType() const
    {
        return _imageType;
    }
    Size getSize() const
    {
        return _rect.getArea() * getBitsPerPixel(_imageType) / 8;
    }

private:
    ImageRect _rect;
    ImageType _imageType;
    static BitsPerPixel getBitsPerPixel(ImageType imageType)
    {
        return bitsPerPixels[imageType];
    }
};

class Image
{
public:
    Image(const ImageFormat& format)
    {
        if (format) _data = make_shared<uint8_t[]>(format.getSize());
    }
    virtual ~Image()
    {
    }
    operator bool() const
    {
        return (_format && _data);
    }
    bool operator!() const
    {
        return (!_format || !_data);
    }
    const ImageFormat& getFormat() const
    {
        return _format;
    }
    Data getData() const
    {
        return _data.get();
    }

private:
    ImageFormat _format;
    ImageData<uint8_t> _data;
};

class Frame: public Image
{
public:
    Frame(const ImageFormat& format) :
            Image(format), _timeStamp(0)
    {
    }
    virtual ~Frame()
    {
    }
    void setTimeStamp(TimeStamp timeStamp)
    {
        _timeStamp = timeStamp;
    }
    TimeStamp getTimeStamp() const
    {
        return _timeStamp;
    }

private:
    TimeStamp _timeStamp;
};

}  // namespace hrm

#endif /* IMAGE_H_ */
