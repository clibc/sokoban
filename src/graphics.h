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
unsigned int create_indexbuffer(unsigned int *indices, size_t bufferSize);

typedef struct
{
    shader context_shader;
    shader texture_shader;
    vertexbuffer texture_vb;
    vertexbuffer context_vb;
    unsigned int context_ib;
    mat4 projection;
    GLint projLoc;
    GLint modelLoc;
} renderer_context;

renderer_context *init_renderer(Window *win);
void destroy_renderer(renderer_context *renderer);
void draw_quad(const renderer_context *context, const vec3 *position, float cube_size);
void draw_colored_quad(const renderer_context *context, const vec3 *position, const vec4 *color, float cube_size);
void draw_textured_quad(const renderer_context *context, const vec3 *position, float cube_size, GLuint textureID);

#endif
