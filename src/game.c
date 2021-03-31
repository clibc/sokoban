#include "game.h"
#include "math.h"

#include <stdlib.h>

Grid create_grid()
{
    Grid retval = {0};
    retval.width = 10;
    retval.height = 10;

    retval.grid_data = (uint32_t *)malloc(retval.width * retval.height * sizeof(uint32_t));
    for (uint32_t i = 0; i < retval.width; ++i)
    {
        for (uint32_t j = 0; j < retval.height; ++j)
        {
            *(retval.grid_data + (i * retval.height + j)) = 1;
        }
    }

    return retval;
}

void render_level(renderer_context *context, const Grid *grid)
{
    vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};

    float x = 41.0f;
    float y = 41.0f;

    for (uint32_t i = 1; i < grid->height; ++i)
    {
        for (uint32_t j = 1; j < grid->width; ++j)
        {
            vec3 position = {x, y, 0.0f};
            draw_colored_quad(context, &position, &color, 40.0f);
            x += 42.0f;
        }
        y += 42.0f;
        x = 41.0f;
    }
}

Quad *malloc_batch_quads(int quad_count)
{
    return (Quad *)malloc(quad_count * sizeof(Quad));
}

unsigned int *malloc_batch_indices(int quad_count)
{
    return (unsigned int *)malloc(quad_count * 6 * sizeof(unsigned int));
}

void create_batch_quad(Quad *quad, int x, int y)
{
    const float stride = 0.9f;

    quad->vertices[0].positions[0] = (float)x;
    quad->vertices[0].positions[1] = (float)y;
    quad->vertices[0].positions[2] = 0.0f;

    quad->vertices[1].positions[0] = (float)x + stride;
    quad->vertices[1].positions[1] = (float)y;
    quad->vertices[1].positions[2] = 0.0f;

    quad->vertices[2].positions[0] = (float)x + stride;
    quad->vertices[2].positions[1] = (float)y + stride;
    quad->vertices[2].positions[2] = 0.0f;

    quad->vertices[3].positions[0] = (float)x;
    quad->vertices[3].positions[1] = (float)y + stride;
    quad->vertices[3].positions[2] = 0.0f;
}

void create_batch_indices(unsigned int *indices, int quad_count)
{
    const int size = quad_count * 6;

    int count = 0;
    for (int i = 0; i < size; i = i + 6)
    {
        indices[i] = count;
        indices[i + 1] = count + 1;
        indices[i + 2] = count + 3;
        indices[i + 3] = count + 1;
        indices[i + 4] = count + 2;
        indices[i + 5] = count + 3;

        count += 4;
    }
}
