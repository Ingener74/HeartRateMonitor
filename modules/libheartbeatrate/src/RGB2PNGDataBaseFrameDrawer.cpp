/*
 * RGB2PNGDataBaseFrameDrawer.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: ingener
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <png.h>

#include "heartratemonitor/RGB2PNGDataBaseFrameDrawer.h"

namespace hrm {

typedef struct  {
    RGB *pixels;
    size_t width;
    size_t height;
} bitmap_t;

RGB2PNGDataBaseFrameDrawer::RGB2PNGDataBaseFrameDrawer(
        const std::string& dataBaseDir) :
        _dataBaseDir(dataBaseDir), _counter(0) {
}

RGB2PNGDataBaseFrameDrawer::~RGB2PNGDataBaseFrameDrawer() {
}

void RGB2PNGDataBaseFrameDrawer::drawFrame(FrameRGB frame) throw (drawError) {

    _counter++;

    _dataBase.put("frames", _counter);

    std::string frameFileName = (format("data_%1$") % _counter).str();

    _dataBase.put("");

    bitmap_t bmp;
    bmp.width = frame.getFormat().rect._cols;
    bmp.height = frame.getFormat().rect._rows;
    bmp.pixels = frame.getData();

    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    /* "status" contains the return value of this function. At first
     it is set to a value which means 'failure'. When the routine
     has finished its work, it is set to a value which means
     'success'. */
    /* The following number is set by trial and error only. I cannot
     see where it it is documented in the libpng manual.
     */
    int pixel_size = 3;
    int depth = 8;

    fp = fopen(frameFileName.c_str(), "wb");
    if (!fp)
        throw "can't open file";

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
        throw "can't create write struct";

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
        throw "can't create info struct";

    /* Set up error handling. */

    if (setjmp(png_jmpbuf (png_ptr)))
        throw "can't set error handling";

    /* Set image attributes. */

    png_set_IHDR(png_ptr, info_ptr, bmp.width, bmp.height, depth,
    PNG_COLOR_TYPE_RGB,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = png_malloc(png_ptr, bmp.height * sizeof(png_byte *));
    for (y = 0; y < bmp.height; ++y) {
        png_byte *row = png_malloc(png_ptr,
                sizeof(uint8_t) * bmp.width * pixel_size);
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
}

} /* namespace hrm */
