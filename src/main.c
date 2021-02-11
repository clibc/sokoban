#include "GLFW/glfw3.h"
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

    while (!glfwWindowShouldClose(window))
    {
        printf("rendering ...\n");
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
