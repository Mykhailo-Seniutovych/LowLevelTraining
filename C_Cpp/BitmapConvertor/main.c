#include "include/bmp-read-utils.h"
#include "include/bmp-structures.h"
#include "include/cmd-utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void applyFilter(FILE *file, int imageWidth, int imageHeight, ColorFilter filterColor);
int getColorIndex(ColorFilter filterColor);

// Example how to run the program: "./bin/app.exe -f img/tree.bmp -c red"

int main(int argc, const char **argv) {
    CmdParams params = parseCmdParams(argc, argv);

    FILE *file;
    if (fopen_s(&file, params.filePath, "rb+") != 0) {
        puts("Cannot open image file");
        exit(1);
    };

    BitmapFileHeader fileHeader;
    readFileHeader(file, &fileHeader);
    DIBHeader dibHeader;
    readDIBHeader(file, &dibHeader);

    fseek(file, fileHeader.pixelDataOffset, 0);

    applyFilter(file, dibHeader.imageWidth, dibHeader.imageHeight, params.colorFilter);

    fclose(file);

    return 0;
}

void applyFilter(FILE *file, int imageWidth, int imageHeight, ColorFilter filterColor) {
    const int pixelSize = 3;
    // count of bytes in one row
    // must be divisible by 4
    const int paddingBytesCount = (imageWidth * pixelSize) % 4 != 0
                                      ? 4 - ((imageWidth * pixelSize) % 4)
                                      : 0;
    int colorIndex = getColorIndex(filterColor);

    for (int yIndex = 0; yIndex < imageHeight; yIndex++) {
        for (int xIndex = 0; xIndex < imageWidth; xIndex++) {
            unsigned char pixel[3];
            int bytesRead = fread(&pixel, 1, 3, file);
            if (bytesRead < 3) {
                puts("Error when reading data from the file.");
                exit(1);
            }

            int colorValue = (int)pixel[colorIndex] + 50;
            colorValue = colorValue <= 255 ? colorValue : 255;
            pixel[colorIndex] = (unsigned char)colorValue;
            fseek(file, -bytesRead, SEEK_CUR);

            // TODO: probably very inefficient way to write three bytes chunks, need to implement some buffer and write larger values at once
            fwrite(&pixel, 1, 3, file);
            fflush(file);
        }
        fseek(file, paddingBytesCount, SEEK_CUR);
    }
}

int getColorIndex(ColorFilter filterColor) {
    // because color is stored as little endian 24 bit integer, the sequence of bytes is Blue, Green, Red
    int index;
    if (filterColor == Red) {
        index = 2;
    } else if (filterColor == Green) {
        index = 1;
    } else {
        index = 0;
    }
    return index;
}