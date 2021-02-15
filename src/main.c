#include "GLFW/glfw3.h"
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sokoban", NULL, NULL);
    assert(window != NULL);

    glfwMakeContextCurrent(window);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    vertexbuffer vb = create_vertexbuffer(&vertices[0], sizeof(vertices));

    shader simpleShader = create_shader("./src/shaders/vertex.vs",
                                        "./src/shaders/fragment.vs");
    //set_vertexbuffer_attibutes(&vb, 0, 3, 3 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    printf("%i\n", glGetError());

    glEnableVertexAttribArray(0);
    printf("%i\n", glGetError());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    printf("%i\n", glGetError());

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
