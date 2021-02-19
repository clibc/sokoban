#include "graphics.h"
#include "matrix.h"
#include "vector.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sokoban", NULL, NULL);
    assert(window != NULL);

    glfwMakeContextCurrent(window);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    shader simpleShader = create_shader("./src/shaders/vertex.vs",
                                        "./src/shaders/fragment.vs");
    glUseProgram(simpleShader.programID);

    mat4 matrix = mat4_ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);

    vec3 vector = {300.0f, 300.0f, 0.0f};
    vec3 vector2 = {200.0f, 100.0f, 0.0f};
    mat4 matrix2 = mat4_translate(mat4_diagonal(1.0f), vector);
    matrix2 = mat4_scale(matrix2, vector2);

    vertexbuffer vb = create_vertexbuffer(vertices, sizeof(vertices));
    set_vertexbuffer_attibutes(&vb, 0, 3, 3 * sizeof(float), (void *)0);

    GLint location = glGetUniformLocation(simpleShader.programID, "projection");
    GLint location2 = glGetUniformLocation(simpleShader.programID, "model");
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix);
    glUniformMatrix4fv(location2, 1, GL_FALSE, &matrix2);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0, 0, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
