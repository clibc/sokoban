#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "vector.h"

typedef struct
{
    vec3 player_position;
    vec3 camera_position;
} Positions;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t *grid_data;
} Grid;

typedef struct
{
    float positions[3];
    float color;
} Vertex;

typedef struct
{
    Vertex vertices[4];
} Quad;

Grid create_grid();
void render_level(renderer_context *context, const Grid *grid);

Quad *malloc_batch_quads(int quad_count);
unsigned int *malloc_batch_indices(int quad_count);

void create_batch_quad(Quad *quad, int x, int y);
void create_batch_indices(unsigned int *indices, int quad_count);

#endif
