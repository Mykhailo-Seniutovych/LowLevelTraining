#ifndef BITMAPCONVERTOR_INCLUDE_BMP_STRUCTURES_H
#define BITMAPCONVERTOR_INCLUDE_BMP_STRUCTURES_H

#include <stdint.h>

typedef struct BitmapFileHeader {
    int16_t fileType;
    int32_t fileSize;
    int16_t reserved1;
    int16_t reserved2;
    int32_t pixelDataOffset;
} BitmapFileHeader;

typedef struct DIBHeader {
    int32_t headerSize;
    int32_t imageWidth;
    int32_t imageHeight;
    int16_t planes;
    int16_t bitsPerPixel;
    int32_t compression;
    int32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    int32_t totalColors;
    int32_t importantColors;
} DIBHeader;

typedef struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;

#endif