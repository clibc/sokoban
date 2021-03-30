#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include "winin.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#include "game.h"

#include <stdlib.h>

int main()
{
    Window *win = create_window("Sokoban", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 0);
    renderer_context *context = init_renderer(win);

    //Grid grid = create_grid();

    Player playr = {vec3_create(41.0f, 41.0f, 0.0f)};

    const float MOVE_DISTANCE = 1.0f;

    const int quad_count = 101;

    unsigned int vb;
    unsigned int ib;

    glGenBuffers(1, &vb);
    glGenBuffers(1, &ib);

    vec3 pos = vec3_create(10.0f, 10.0f, 0.0f);
    mat4 temp = mat4_diagonal(1.0f);
    temp = mat4_translate(&temp, &pos);

    vec3 scale_vector = {50, 50, 0.0f};
    temp = mat4_scale(&temp, &scale_vector);
    glUseProgram(context->context_shader.programID);
    glUniformMatrix4fv(context->modelLoc, 1, GL_FALSE, (GLfloat *)&temp);

    playr.position.x = 0;
    playr.position.y = 0;

    Quad *quads = malloc_batch_quads(quad_count);
    unsigned int *indices = malloc_batch_indices(quad_count);

    ///////
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

        {
            int count = 0;
            for (int i = 0; i < 10; ++i)
            {
                for (int j = 0; j < 10; ++j)
                {
                    create_batch_quad(&quads[count], j, i);
                    count++;
                }
            }

            {
                Quad *quad = &quads[quad_count - 1];
                int x = playr.position.x;
                int y = playr.position.y;

                const float stride = 0.9f;

                quad->vertices[0].positions[0] = (float)x;
                quad->vertices[0].positions[1] = (float)y;
                quad->vertices[0].positions[2] = 0.0f;
                quad->vertices[0].color = 1.0f;

                quad->vertices[1].positions[0] = (float)x + stride;
                quad->vertices[1].positions[1] = (float)y;
                quad->vertices[1].positions[2] = 0.0f;
                quad->vertices[1].color = 1.0f;

                quad->vertices[2].positions[0] = (float)x + stride;
                quad->vertices[2].positions[1] = (float)y + stride;
                quad->vertices[2].positions[2] = 0.0f;
                quad->vertices[2].color = 1.0f;

                quad->vertices[3].positions[0] = (float)x;
                quad->vertices[3].positions[1] = (float)y + stride;
                quad->vertices[3].positions[2] = 0.0f;
                quad->vertices[3].color = 1.0f;
            }

            create_batch_indices(indices, quad_count);

            glBindBuffer(GL_ARRAY_BUFFER, vb);
            glBufferData(GL_ARRAY_BUFFER, quad_count * sizeof(Quad), quads, GL_DYNAMIC_DRAW);
            set_vertexbuffer_attibutes((vertexbuffer *)&vb, 0, 3, 4 * sizeof(float), (void *)0);
            set_vertexbuffer_attibutes((vertexbuffer *)&vb, 1, 1, 4 * sizeof(float), (void *)(sizeof(float) * 3));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_count * 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
            glUseProgram(context->context_shader.programID);
        }

        glDrawElements(GL_TRIANGLES, quad_count * 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(win->handle);
        glfwPollEvents();
    }

    destroy_renderer(context);
    destroy_window(win);
    return 0;
}
