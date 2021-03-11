#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    I_PNG,
    I_JPG
} IMAGE_TYPE;

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
    unsigned int width;
    unsigned int height;
    char bit_depth;
    char color_type;
    char complession_method;
    char filter_method;
    char interlace_method;
} PNG_HEADER;
#pragma pack(pop)

static char *load_png(const char *filepath)
{
    char *buffer = read_entire_file(filepath);
    assert(buffer != NULL);

    PNG_HEADER header = {0};
    memcpy(&header, buffer + 16, sizeof(PNG_HEADER));
    header.width = swap_byte_int(header.width);
    header.height = swap_byte_int(header.height);

    int lenght;
    memcpy(&lenght, buffer + 33, 4);
    lenght = swap_byte_int(lenght);

    char *image_data = (char *)malloc(lenght * sizeof(char));
    memcpy(&image_data[0], buffer + 41, lenght);

    char header_byte = *image_data;
    char bfinal = (char)(header_byte & 1);
    char btype = (char)(header_byte & 2);

    printf("%i, %i\n", bfinal, btype);

    return image_data;
}

#endif
