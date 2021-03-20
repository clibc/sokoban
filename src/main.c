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

    vec3 position = {300.0f, 300.0f, 0.0f};

    vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};

    Grid grid = create_grid();

    while (!glfwWindowShouldClose(win->handle))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        if (get_key_down(GLFW_KEY_A))
        {
            printf("A is pressed...\n");
        }
        if (get_key_down(GLFW_KEY_D))
        {
            printf("D is pressed...\n");
        }

        render_level(context, grid);

        glfwSwapBuffers(win->handle);
        glfwPollEvents();
    }

    destroy_renderer(context);
    destroy_window(win);
    return 0;
}
