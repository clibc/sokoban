#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GLEW/glew.h"
#include <stddef.h>

#include "matrix.h"
#include "winin.h"

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

typedef struct
{
    shader context_shader;
    vertexbuffer context_vb;
    mat4 projection;
    mat4 model;
    GLint projLoc;
    GLint modelLoc;
} renderer_context;

renderer_context *init_renderer(Window *win);
void *destroy_renderer(renderer_context *renderer);
void draw_quad(renderer_context *context, const vec3 *position, float cube_size);
void draw_colored_quad(renderer_context *context, vec3 position, vec3 color);

#endif
