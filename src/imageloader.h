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
    unsigned int file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    unsigned int offset;
} BMP_HEADER;
#pragma pack(pop)

static char *load_bmp(const char *filepath)
{
    char *file = read_entire_file(filepath);

    BMP_HEADER header = {0};
    memcpy(&header, file, sizeof(BMP_HEADER));

    return file;
}

// FUCK PNG LOAD BMP

#endif
