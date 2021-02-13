#include "GLFW/glfw3.h"
#include "matrix.h"
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

    mat4 matrix1 = {0.0f};
    matrix1.values[0][0] = 1;
    matrix1.values[1][0] = 2;
    matrix1.values[2][0] = 2;
    matrix1.values[3][0] = 5;

    matrix1.values[0][1] = 2;
    matrix1.values[1][1] = 1;
    matrix1.values[2][1] = 2;
    matrix1.values[3][1] = 6;
    // test
    matrix1.values[0][2] = 3;
    matrix1.values[1][2] = 3;
    matrix1.values[2][2] = 1;
    matrix1.values[3][2] = 7;

    matrix1.values[0][3] = 3;
    matrix1.values[1][3] = 2;
    matrix1.values[2][3] = 4;
    matrix1.values[3][3] = 1;

    mat4 matrix2 = {0.0f};

    matrix2.values[0][0] = 2;
    matrix2.values[1][0] = 4;
    matrix2.values[2][0] = 4;
    matrix2.values[3][0] = 5;

    matrix2.values[0][1] = 3;
    matrix2.values[1][1] = 9;
    matrix2.values[2][1] = 6;
    matrix2.values[3][1] = 6;

    matrix2.values[0][2] = 6;
    matrix2.values[1][2] = 3;
    matrix2.values[2][2] = 4;
    matrix2.values[3][2] = 7;

    matrix2.values[0][3] = 7;
    matrix2.values[1][3] = 4;
    matrix2.values[2][3] = 5;
    matrix2.values[3][3] = 7;

    mat4 result = mat4_multiply(matrix1, matrix2);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("%f ", matrix1.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("%f ", matrix2.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            printf("%f ", result.values[i][j]);
        }
        printf("\n");
    }

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
