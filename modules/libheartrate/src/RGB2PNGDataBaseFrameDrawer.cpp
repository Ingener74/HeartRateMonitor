/*
 * RGB2PNGDataBaseFrameDrawer.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: ingener
 */

#include <png.h>

#include <HeartRate/HeartRateTools.h>
#include <HeartRate/RGB2PNGDataBaseFrameDrawer.h>

namespace hrm {

using namespace std;
using namespace boost;

typedef struct  {
    RGB *pixels;
    size_t width;
    size_t height;
} bitmap_t;

RGB2PNGDataBaseFrameDrawer::RGB2PNGDataBaseFrameDrawer(
        const std::string& dataBaseDir) :
        _dataBaseDir(dataBaseDir), _counter(0) {
    cout << format("data base dir %1%") % _dataBaseDir;
}

RGB2PNGDataBaseFrameDrawer::~RGB2PNGDataBaseFrameDrawer() {

    cout << "RGB2PNGDataBaseFrameDrawer::~RGB2PNGDataBaseFrameDrawer()";

    try {
        property_tree::write_json(_dataBaseDir + "/database.json", _dataBase);
    } catch (const property_tree::json_parser_error& e) {
        cerr << format("error in rgb to png data base frame drawer: %1%")
                % e.what();
    }
}

void RGB2PNGDataBaseFrameDrawer::drawFrame(FrameRGB frame)
{
	if (_dataBaseDir.empty()) throw runtime_error("data base dir path empty");

    _counter++;

    std::string frameFileName, framePath;


    try {
        _dataBase.put("frames", _counter);

       frameFileName = (
               format("data_%1%.png") % _counter).str();
       framePath = _dataBaseDir + "/" + frameFileName;

       _dataBase.put<std::string>((
               format("data_%1%.file") % _counter).str(), frameFileName);
       _dataBase.put<TimeStamp>((
               format("data_%1%.timestamp") % _counter).str(), frame.getTimeStamp());

       bitmap_t bmp;
       bmp.width = frame.getFormat().rect._cols;
       bmp.height = frame.getFormat().rect._rows;
       bmp.pixels = frame.getData();

       FILE * fp;
       png_structp png_ptr = NULL;
       png_infop info_ptr = NULL;
       size_t x, y;
       png_byte ** row_pointers = NULL;
       int pixel_size = 3;
       int depth = 8;

       fp = fopen(framePath.c_str(), "wb");
       if (!fp)
           throw runtime_error("can't open file");


       png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
       if (png_ptr == NULL)
           throw runtime_error("can't create write struct");

       info_ptr = png_create_info_struct(png_ptr);
       if (info_ptr == NULL)
           throw runtime_error("can't create info struct");

       /* Set up error handling. */

       if (setjmp(png_jmpbuf (png_ptr)))
           throw runtime_error("can't set error handling");

       /* Set image attributes. */

       png_set_IHDR(png_ptr, info_ptr, bmp.width, bmp.height, depth,
       PNG_COLOR_TYPE_RGB,
       PNG_INTERLACE_NONE,
       PNG_COMPRESSION_TYPE_DEFAULT,
       PNG_FILTER_TYPE_DEFAULT);

       /* Initialize rows of PNG. */

       row_pointers = static_cast<png_byte **>(
               png_malloc(png_ptr, bmp.height * sizeof(png_byte *)));
       for (y = 0; y < bmp.height; ++y) {
           png_byte *row = static_cast<png_byte *>(png_malloc(png_ptr,
                   sizeof(uint8_t) * bmp.width * pixel_size));
           row_pointers[y] = row;
           for (x = 0; x < bmp.width; ++x) {
               RGB * pixel = bmp.pixels + bmp.width * y + x;
               *row++ = pixel->r;
               *row++ = pixel->g;
               *row++ = pixel->b;
           }
       }

       /* Write the image data to "fp". */

       png_init_io(png_ptr, fp);
       png_set_rows(png_ptr, info_ptr, row_pointers);
       png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

       /* The routine has successfully written the file, so we set
        "status" to a value which indicates success. */

       for (y = 0; y < bmp.height; y++) {
           png_free(png_ptr, row_pointers[y]);
       }
       png_free(png_ptr, row_pointers);

       png_destroy_write_struct(&png_ptr, &info_ptr);
       fclose(fp);

    } catch (const property_tree::json_parser_error& e) {
        throw runtime_error("data base put error");
    } catch (...){
        throw runtime_error("data base fatal error");
    }
}

} /* namespace hrm */
