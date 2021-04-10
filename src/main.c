#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include "winin.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#include "game.h"

#include <stdlib.h>

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

vec3 vec3_lerp(vec3 a, vec3 b, float f)
{
    vec3 retval = vec3_create(0.0f, 0.0f, 0.0f);

    retval.x = lerp(a.x, b.x, f);
    retval.y = lerp(a.y, b.y, f);
    return retval;
}

vec3 camera_lookat(vec3 target)
{
    // assume screen size is 600x600
    const camera_size_half = -300.0f / 2.0f;
    vec3 retval = {0.0f};

    retval.x = (target.x / 2.0f) - camera_size_half;
    retval.y = (target.y / 2.0f) - camera_size_half;

    return retval;
}

int main()
{
    Window *win = create_window("Sokoban", WINDOW_WIDTH, WINDOW_HEIGHT, 3, 0);
    renderer_context *context = init_renderer(win);

    Positions playr = {vec3_create(0.0f, 0.0f, 0.0f), {0.0f, 0.0f, 0.0f}};

    const float MOVE_DISTANCE = 100.0f;

    const int quad_count = 100;

    unsigned int vb;
    unsigned int ib;

    glGenBuffers(1, &vb);
    glGenBuffers(1, &ib);

    vec3 pos = vec3_create(10.0f, 10.0f, 0.0f);
    mat4 temp = mat4_diagonal(1.0f);
    temp = mat4_translate(&temp, &pos);

    vec3 scale_vector = {50, 50, 0.0f};
    temp = mat4_scale(&temp, &scale_vector);
    glUseProgram(context->batch_shader.programID);
    int mloc = glGetUniformLocation(context->batch_shader.programID, "model");
    glUniformMatrix4fv(mloc, 1, GL_FALSE, (GLfloat *)&temp);

    Quad *quads = malloc_batch_quads(quad_count);
    unsigned int *indices = malloc_batch_indices(quad_count);

    mat4 view_matrix = mat4_diagonal(1.0f);
    view_matrix = mat4_translate(&view_matrix, &playr.camera_position);

    vec3 scaleview = vec3_create(2.0f, 2.0f, 0.0f);
    view_matrix = mat4_translate(&view_matrix, &playr.camera_position);
    view_matrix = mat4_scale(&view_matrix, &scaleview);
    int loc = glGetUniformLocation(context->batch_shader.programID, "view");
    int color_loc = glGetUniformLocation(context->batch_shader.programID, "u_color");
    if (loc != -1)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&view_matrix);
    }
    else
        printf("Failed to get location");

    int interpolationFramesCount = 45;
    int elapsedFrames = 0;

    vec3 playerColor = vec3_create(1.0f, 0.0f, 0.0f);
    vec3 playerPos = pos;

    vec3 oldtransform = camera_lookat(playerPos);
    vec3 newtransform = oldtransform;

    while (!glfwWindowShouldClose(win->handle))
    {
        float interpolationRatio = (float)elapsedFrames / interpolationFramesCount;
        fill_screen_with_color(21, 21, 21, 1);

        const CAMERAMOVE = MOVE_DISTANCE * 2.0f;

        if (get_key_down(GLFW_KEY_A))
        {

            playerPos.x -= MOVE_DISTANCE;
            newtransform.x += CAMERAMOVE;
        }
        else if (get_key_down(GLFW_KEY_D))
        {
            playerPos.x += MOVE_DISTANCE;
            newtransform.x -= CAMERAMOVE;
        }
        else if (get_key_down(GLFW_KEY_W))
        {
            playerPos.y += MOVE_DISTANCE;
            newtransform.y -= CAMERAMOVE;
        }
        else if (get_key_down(GLFW_KEY_S))
        {
            playerPos.y -= MOVE_DISTANCE;
            newtransform.y += CAMERAMOVE;
        }

        oldtransform = vec3_lerp(oldtransform, newtransform, interpolationRatio);
        view_matrix = mat4_translate(&view_matrix, &oldtransform);

        elapsedFrames = (elapsedFrames + 1) % (interpolationFramesCount + 1);

        glUseProgram(context->batch_shader.programID);
        glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&view_matrix);

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
            create_batch_indices(indices, quad_count);

            glBindBuffer(GL_ARRAY_BUFFER, vb);
            glBufferData(GL_ARRAY_BUFFER, quad_count * sizeof(Quad), quads, GL_DYNAMIC_DRAW);
            set_vertexbuffer_attibutes((vertexbuffer *)&vb, 0, 3, 3 * sizeof(float), (void *)0);

            vec4 cube_color = {0.0f, 1.0f, 0.0f, 1.0f};
            glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&view_matrix);
            glUniformMatrix4fv(mloc, 1, GL_FALSE, (GLfloat *)&temp);
            glUniform4fv(color_loc, 1, (GLfloat *)&cube_color);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_count * 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
            glDrawElements(GL_TRIANGLES, quad_count * 6, GL_UNSIGNED_INT, 0);
        }

        glUseProgram(context->batch_shader.programID);
        glBindBuffer(GL_ARRAY_BUFFER, context->context_vb.bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->context_ib);

        mat4 temp = mat4_diagonal(1.0f);
        temp = mat4_translate(&temp, &playerPos);

        vec3 scale_vector = {50.0f, 50.0f, 0.0f};
        temp = mat4_scale(&temp, &scale_vector);

        glUniformMatrix4fv(mloc, 1, GL_FALSE, (GLfloat *)&temp);
        glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat *)&view_matrix);
        glUniform4fv(color_loc, 1, (GLfloat *)&playerColor);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //draw_colored_quad(context, &playerPos, &playerColor, 100.0f);

        glfwSwapBuffers(win->handle);
        glfwPollEvents();
    }

    destroy_renderer(context);
    destroy_window(win);
    return 0;
}
