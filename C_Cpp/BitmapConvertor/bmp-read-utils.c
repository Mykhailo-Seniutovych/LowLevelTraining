#include "include/bmp-read-utils.h"
#include "include/bmp-structures.h"
#include <stdlib.h>

void readFileHeader(FILE *file, BitmapFileHeader *fileHeader) {
    fread(&(fileHeader->fileType), sizeof(fileHeader->fileType), 1, file);
    fread(&(fileHeader->fileSize), sizeof(fileHeader->fileSize), 1, file);
    fread(&(fileHeader->reserved1), sizeof(fileHeader->reserved1), 1, file);
    fread(&(fileHeader->reserved2), sizeof(fileHeader->reserved2), 1, file);
    fread(&(fileHeader->pixelDataOffset), sizeof(fileHeader->pixelDataOffset), 1, file);
}

void readDIBHeader(FILE *file, DIBHeader *dibHeader) {
    fread(&(dibHeader->headerSize), sizeof(dibHeader->headerSize), 1, file);
    fread(&(dibHeader->imageWidth), sizeof(dibHeader->imageWidth), 1, file);
    fread(&(dibHeader->imageHeight), sizeof(dibHeader->imageHeight), 1, file);
    fread(&(dibHeader->planes), sizeof(dibHeader->planes), 1, file);
    fread(&(dibHeader->bitsPerPixel), sizeof(dibHeader->bitsPerPixel), 1, file);
    fread(&(dibHeader->compression), sizeof(dibHeader->compression), 1, file);
    fread(&(dibHeader->imageSize), sizeof(dibHeader->imageSize), 1, file);
    fread(&(dibHeader->xPixelsPerMeter), sizeof(dibHeader->xPixelsPerMeter), 1, file);
    fread(&(dibHeader->yPixelsPerMeter), sizeof(dibHeader->yPixelsPerMeter), 1, file);
    fread(&(dibHeader->totalColors), sizeof(dibHeader->totalColors), 1, file);
    fread(&(dibHeader->importantColors), sizeof(dibHeader->importantColors), 1, file);

    if (dibHeader->bitsPerPixel != 24) {
        printf("image has %d bit color, this tool supports only 24 bit color images", dibHeader->bitsPerPixel);
        exit(1);
    }
}

void readSinglePixel(FILE *file, Pixel *pixel) {
    fread(&(pixel->red), sizeof(pixel->red), 1, file);
    fread(&(pixel->red), sizeof(pixel->red), 1, file);
    fread(&(pixel->red), sizeof(pixel->red), 1, file);
};