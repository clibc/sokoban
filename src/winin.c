#include "winin.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Window *create_window(const char *name, int width, int height, int glMajor, int glMinor)
{
    Window *retval = (Window *)malloc(sizeof(Window));

    if (!glfwInit())
    {
        printf("glfwInit() failed\n");
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);

    retval->handle = glfwCreateWindow(width, height, name, NULL, NULL);

    assert(retval->handle != GLEW_OK);

    glfwMakeContextCurrent(retval->handle);

    if (glewInit() != 0)
    {
        printf("glewInit() failed\n");
        exit(-1);
    }

    return retval;
}
