#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include "winin.h"

#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#include "imageloader.h"

#include "game.h"

int main(int argc, char *argv[])
{
    Window *win = create_window("Sokoban", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 0);
    renderer_context *context = init_renderer(win);

    Grid grid = create_grid();

    //c
    Player playr = {vec3_create(41.0f, 41.0f, 0.0f)};
    vec4 color = {0.0f, 1.0f, 0.0f, 1.0f};

    const float MOVE_DISTANCE = 42.0f;

    while (!glfwWindowShouldClose(win->handle))
    {
        fill_screen_with_color(21, 21, 21, 1);

        if (get_key_down(GLFW_KEY_A))
        {
            playr.position.x -= MOVE_DISTANCE;
        }
        else if (get_key_down(GLFW_KEY_D))
        {
            playr.position.x += MOVE_DISTANCE;
        }
        else if (get_key_down(GLFW_KEY_W))
        {
            playr.position.y += MOVE_DISTANCE;
        }
        else if (get_key_down(GLFW_KEY_S))
        {
            playr.position.y -= MOVE_DISTANCE;
        }

        render_level(context, &grid);
        draw_colored_quad(context, &playr.position, &color, 40.0f);

        glfwSwapBuffers(win->handle);
        glfwPollEvents();
    }

    destroy_renderer(context);
    destroy_window(win);
    return 0;
}
