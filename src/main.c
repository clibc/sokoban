#include "GLFW/glfw3.h"
#include "vector.h"
#include <stdio.h>

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        printf("failed to initialize glfw!\n");
        return 0;
    }

    window = glfwCreateWindow(600, 600, "Sokoban", NULL, NULL);

    glfwMakeContextCurrent(window);

    vec2 textvec = {0.4f, 1.8f};
    vec2 textvec1 = {1.0f, 0.5f};

    vec2 result = vec2_multiply(textvec, textvec1);

    /* while (!glfwWindowShouldClose(window)) */
    /* { */
    /*     printf("rendering ...\n"); */
    /*     glClearColor(1.0f, 0.0f, 0.0f, 1.0f); */
    /*     glClear(GL_COLOR_BUFFER_BIT); */
    /*     glfwSwapBuffers(window); */
    /*     glfwPollEvents(); */
    /* } */
    glfwTerminate();
    return 0;
}
