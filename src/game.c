#include "game.h"
#include "math.h"

#include <stdlib.h>

Grid create_grid()
{
    Grid retval = {0};
    retval.width = 10;
    retval.height = 5;

    retval.grid_data = (uint32_t *)malloc(retval.width * retval.height * sizeof(uint32_t));
    for (int i = 0; i < retval.width; ++i)
    {
        for (int j = 0; j < retval.height; ++j)
        {
            *(retval.grid_data + (i * retval.height + j)) = 1;
        }
    }
}

void render_level(renderer_context *context, const Grid *grid)
{
    vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};

    for (int i = 0; i < grid->width; ++i)
    {
        for (int j = 0; j < grid->height; ++j)
        {
            vec3 position = {i * 42.0f, j * 42.0f, 0.0f};
            draw_colored_quad(context, &position, &color, 40.0f);
        }
    }
}
