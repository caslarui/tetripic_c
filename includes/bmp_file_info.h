// Copyright [2019] <Ligia Dolinta 311CD>
#ifndef _BMP_FILEINFO_H_
# define _BMP_FILEINFO_H_

#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

typedef struct {
    uint16_t        filetype; /* 'BM' */
    uint32_t        bfSize; /* File's size */
    uint16_t        unused1;
    uint16_t        unused2;
    uint32_t        imageDataOffset; /* Offset to the start of image data */
}bmp_fileheader; // 14bytes

typedef struct {
    uint32_t        biSize; /* Size of the info header - 40 bytes */
    int32_t         width; /* Width of the image */
    int32_t         height; /* Height of the image */

    uint16_t        planes;
    uint16_t        bitPix;
    uint32_t        biCompression;
    uint32_t        biSizeImage; /* Size of the image data */
    int32_t         biXPelsPerMeter;
    int32_t         biYPelsPerMeter;
    uint32_t        biClrUsed;
    uint32_t        biClrImportant;
}bmp_infoheader; // 40bytes

#pragma pack()

typedef struct {
    uint8_t         B;
    uint8_t         G;
    uint8_t         R;
}bmp_pixelcolor;

#endif
