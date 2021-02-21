#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GLEW/glew.h"
#include <stddef.h>

typedef struct
{
    GLuint programID;
} shader;

shader create_shader(const char *vshader, const char *fshader);
char *_load_file(const char *filepath);

typedef struct
{
    GLuint bufferID;
    float *vertices;
    size_t buffer_size;
} vertexbuffer;

vertexbuffer create_vertexbuffer(float *vertices, size_t bufferSize);
void set_vertexbuffer_attibutes(vertexbuffer *vb,
                                int index,
                                size_t size,
                                size_t stride,
                                void *pointer);
#endif
