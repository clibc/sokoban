#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

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

static int load_png(const char *filepath)
{
    char *buffer = read_entire_file(filepath);

    // Parse Data

    unsigned int lenght;

    memcpy(&lenght, buffer + 33, 4);

    return lenght;
}

#endif
