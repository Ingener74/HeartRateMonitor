/*
 * PNGDataBase2RGBFrameSource.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#include <png.h>

#include <heartrate/HeartRateTools.h>
#include <heartrate/PNGDataBase2RGBFrameSource.h>

namespace hrm {

PNGDataBase2RGBFrameSource::PNGDataBase2RGBFrameSource(
        const std::string& dataBaseDir) :
        _dataBaseDir(dataBaseDir), _currentFrame(0), _frameCount(0), _delay(0), _fsTimeStamp(0){

    property_tree::read_json(_dataBaseDir + "/database.json", _dataBase);
    _frameCount = _dataBase.get<int>("frames");
    if(!_frameCount)
        throw HRFrameSourceException("frame count is zero");
}

PNGDataBase2RGBFrameSource::~PNGDataBase2RGBFrameSource() {
}

FrameSharedLockedRGB PNGDataBase2RGBFrameSource::getFrame()
        throw (HRFrameSourceException) {

    this_thread::sleep(posix_time::milliseconds(_delay));

    {
        unique_lock<shared_mutex> lock(_frameMutex);
        _currentFrame++;

        TimeStamp ts, tsNext;

        if(_currentFrame >= (_frameCount - 1)){
            _delay = 0;
            _currentFrame = 1;
        }else{
            ts = _dataBase.get<TimeStamp>((
                    format("data_%1%.timestamp") % _currentFrame
                    ).str());

            tsNext = _dataBase.get<TimeStamp>((
                    format("data_%1%.timestamp") % (_currentFrame + 1)
                    ).str());

            _delay = tsNext - ts;
        }

        _fsTimeStamp += _delay;

        const std::string frameFileName = _dataBase.get<std::string>((
                    format("data_%1%.file") % _currentFrame
                    ).str());
        const std::string framePath = _dataBaseDir + "/" + frameFileName;

//        HRM_DEBUG((boost::format("png data base file name %1%") % framePath ).str());

        /*
         * was global
         */
        int x, y;

        int width, height;
        png_byte color_type;
        png_byte bit_depth;

        png_structp png_ptr;
        png_infop info_ptr;
        int number_of_passes;
        png_bytep * row_pointers;
        /*
         *
         */

        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(framePath.c_str(), "rb");
        if (!fp)
            throw HRFrameSourceException((
                    boost::format("[read_png_file] File %1% could not be opened for reading") % frameFileName
                    ).str());

        fread(header, 1, 8, fp);
        if (png_sig_cmp(reinterpret_cast<const unsigned char*>(header), 0, 8))
            throw HRFrameSourceException((
                    boost::format("[read_png_file] File %1% is not recognized as a PNG file") % frameFileName
                    ).str());


        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
            throw HRFrameSourceException(
                    "[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
            throw HRFrameSourceException(
                    "[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
            throw HRFrameSourceException("[read_png_file] Error during init_io");

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);

        ImageRect imRect(height, width);
        if(_frame.getFormat().rect != imRect){
            _frame = FrameRGB(TypeImageFormat<RGB>(imRect));
        }

        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
            throw HRFrameSourceException("[read_png_file] Error during read_image");

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

        for (y = 0; y < height; y++)
            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

        png_read_image(png_ptr, row_pointers);

        RGB * dst = _frame.getData();

        for (int i = 0, imax = imRect._rows; i < imax; ++i) {
            uint8_t * rows_src = row_pointers[i];
            for (int j = 0, jmax = imRect._cols; j < jmax; ++j) {
                dst->b = *rows_src++;
                dst->g = *rows_src++;
                dst->r = *rows_src++;
                dst++;
            }
        }

        _frame.setTimeStamp(_fsTimeStamp);

        for (y = 0; y < height; y++) {
            png_free(png_ptr, row_pointers[y]);
        }
        png_free(png_ptr, row_pointers);

        fclose(fp);
    }
    FrameSharedLockedRGB lockedFrame(
            boost::shared_ptr<boost::shared_lock<boost::shared_mutex> >(
                    new boost::shared_lock<boost::shared_mutex>(_frameMutex)),
                    _frame);
    return lockedFrame;
}

} /* namespace hrm */
