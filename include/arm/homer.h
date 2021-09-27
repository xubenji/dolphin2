/*  GIMP header image file format (RGB)  */

static unsigned int homer_width = 1024;
static unsigned int homer_height = 768;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */

#define HEADER_PIXE(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}
