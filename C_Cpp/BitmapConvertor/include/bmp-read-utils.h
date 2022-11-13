#ifndef BITMAPCONVERTOR_INCLUDE_BMP_READ_UTILITIES_H
#define BITMAPCONVERTOR_INCLUDE_BMP_READ_UTILITIES_H

#include "bmp-structures.h"
#include <stdio.h>

void readFileHeader(FILE *file, BitmapFileHeader *fileHeader);
void readDIBHeader(FILE *file, DIBHeader *dibHeader);
void readSinglePixel(FILE *file, Pixel *pixel);

#endif