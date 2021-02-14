#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GLFW/glfw3.h"
#include <stddef.h>

typedef struct
{
    GLFWwindow *window;
    int width;
    int height;
} window;

window create_window(const char *name, int width, int height);
void swap_buffer();

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
