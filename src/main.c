#include "GLFW/glfw3.h"
#include "vector.h"
#include <math.h>
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

    vec2 textvec = {-12.0f, 16.0f};
    vec2 textvec1 = {12.0f, 9.0f};

    float resultdot = vec2_dot(textvec, textvec1);
    float result1 = vec2_magnitude(textvec);

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
