#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include "winin.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#include "game.h"

#include <stdlib.h>

void generate_batch_quad(float *array, int x, int y)
{
    const float stride = 0.9f;

    array[0] = (float)x;
    array[1] = (float)y;
    array[2] = 0.0f;

    array[3] = (float)x + stride;
    array[4] = (float)y;
    array[5] = 0.0f;

    array[6] = (float)x + stride;
    array[7] = (float)y + stride;
    array[8] = 0.0f;

    array[9] = (float)x;
    array[10] = (float)y + stride;
    array[11] = 0.0f;
}

float *create_positions_for_grid(int x, int y, float space_size)
{
    size_t buffer_size = x * y * 12 * sizeof(float);
    float *positions = (float *)malloc(buffer_size);

    unsigned int count = 0;

    // 1 = x,y
    // 2 = x, y-1
    // 3 = x-1, y-1
    // 4 = x-1, y

    for (int i = 0; i < y; ++i)
    {
        for (int j = 0; j < x; ++j)
        {
            generate_batch_quad(&positions[count], j, i);
            count += 12;
        }
    }
    return positions;
}

unsigned int *create_indices(int quad_count)
{
    const int size = quad_count * 6;
    unsigned int *indices = (unsigned int *)malloc(size * sizeof(int));

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

    return indices;
}

int main()
{
    Window *win = create_window("Sokoban", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 0);
    renderer_context *context = init_renderer(win);

    //Grid grid = create_grid();

    Player playr = {vec3_create(41.0f, 41.0f, 0.0f)};

    const float MOVE_DISTANCE = 42.0f;

    const int quad_count = 100;

    float *vertices = create_positions_for_grid(10, 10, 1.0f);
    unsigned int *indices = create_indices(quad_count);

    vertexbuffer vb = create_vertexbuffer(vertices, sizeof(float) * quad_count * 12);
    set_vertexbuffer_attibutes(&vb, 0, 3, 3 * sizeof(float), (void *)0);
    unsigned int ib = create_indexbuffer(indices, sizeof(unsigned int) * quad_count * 6);

    ///////
    glUseProgram(context->context_shader.programID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

    vec3 pos = vec3_create(10.0f, 10.0f, 0.0f);
    mat4 temp = mat4_diagonal(1.0f);
    temp = mat4_translate(&temp, &pos);

    vec3 scale_vector = {50, 50, 0.0f};
    temp = mat4_scale(&temp, &scale_vector);

    glUniformMatrix4fv(context->modelLoc, 1, GL_FALSE, (GLfloat *)&temp);

    vec4 def_color = {0.0f, 1.0f, 0.0f, 1.0f};
    unsigned int loc = glGetUniformLocation(context->context_shader.programID, "u_color");
    glUniform4fv(loc, 1, (GLfloat *)&def_color);

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

        /* render_level(context, &grid); */
        /* draw_colored_quad(context, &playr.position, &color, 40.0f); */

        glDrawElements(GL_TRIANGLES, quad_count * 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(win->handle);
        glfwPollEvents();
    }

    destroy_renderer(context);
    destroy_window(win);
    return 0;
}
