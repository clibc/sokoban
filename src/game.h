#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "vector.h"

typedef struct
{
    vec3 position;
} Player;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t *grid_data;
} Grid;

typedef struct
{
    float positions[3];
} Vertex;

typedef struct
{
    Vertex vertices[4];
} Quad;

Grid create_grid();
void render_level(renderer_context *context, const Grid *grid);

Quad create_quad(float x, float y);

#endif
