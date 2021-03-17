#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_entire_file(const char *filepath)
{
    char *buffer;
    int size = 0;
    FILE *file = fopen(filepath, "rb");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        buffer = (char *)malloc((sizeof(char) * size));
        fread(buffer, sizeof(char), size, file);
    }
    else
    {
        printf("File is not found: %s\n", filepath);
        return NULL;
    }
    return buffer;
}

static inline int swap_byte_int(int value)
{
    int swapped = (value & 0x000000FF) << 24;
    swapped = swapped | ((value & 0x0000FF00) << 8);
    swapped = swapped | ((value & 0x00FF0000) >> 8);
    swapped = swapped | ((value & 0xFF000000) >> 24);

    return swapped;
}

#pragma pack(push, 1)
typedef struct
{
    uint16_t header_field;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHEADER;

typedef struct
{
    uint32_t sizeof_header;
    uint32_t width;
    uint32_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t numberofcolors_colorpalette;
    uint32_t numberofcolors_important;

} BITMAPCOREHEADER;
#pragma pack(pop)

static char *load_bmp(const char *filepath, unsigned int *width, unsigned int *height)
{
    char *file = read_entire_file(filepath);

    BMPHEADER header = {0};
    BITMAPCOREHEADER core = {0};
    memcpy(&header, file, sizeof(BMPHEADER));

    char *dibHeader = file + sizeof(BMPHEADER);
    memcpy(&core, dibHeader, sizeof(BITMAPCOREHEADER));

    printf("Image data offset : %d\n", header.offset);
    printf("File size : %d\n", header.file_size);
    printf("Width : %d\n", core.width);
    printf("Height : %d\n", core.height);
    printf("Bits per pixel : %d\n", core.bits_per_pixel);
    printf("Compression method : %x\n", core.compression_method);
    printf("Image Size : %d\n", core.image_size);
    printf("H res : %d\n", core.horizontal_resolution);
    printf("V res : %d\n", core.vertical_resolution);
    printf("N color palette : %d\n", core.numberofcolors_colorpalette);
    printf("N color important : %d\n", core.numberofcolors_important);

    *width = core.width;
    *height = core.height;

    return file + header.offset;
}

// FUCK PNG LOAD BMP

#endif
