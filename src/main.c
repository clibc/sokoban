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

    mat4 projection = mat4_ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);

    vec3 vector = {300.0f, 300.0f, 0.0f};
    vec3 vector2 = {100.0f, 100.0f, 0.0f};
    mat4 model = mat4_translate(mat4_diagonal(1.0f), vector);
    model = mat4_scale(model, vector2);
    mat4 rotate = mat4_rotate(-180.0f, vec3_create(0, 0, 1));
    model = mat4_multiply(model, rotate);

    vec3 test_vec = {0.5, 2.0f, 1.0f};
    vec4 test = mat4_multiply_vec3(model, test_vec);

    vertexbuffer vb = create_vertexbuffer(vertices, sizeof(vertices));
    set_vertexbuffer_attibutes(&vb, 0, 3, 3 * sizeof(float), (void *)0);

    GLint location = glGetUniformLocation(simpleShader.programID, "projection");
    GLint location2 = glGetUniformLocation(simpleShader.programID, "model");

    printf("%i\n", location);
    glUniformMatrix4fv(location, 1, GL_FALSE, &projection);
    glUniformMatrix4fv(location2, 1, GL_FALSE, &model);

    while (!glfwWindowShouldClose(window))
    {
        float angle = sin(30);
        rotate = mat4_rotate(angle, vec3_create(0, 0, 1));
        model = mat4_multiply(model, rotate);
        glUniformMatrix4fv(location2, 1, GL_FALSE, &model);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0, 0, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
