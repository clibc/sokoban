#include "winin.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Window *create_window(const char *name, int width, int height, int glMajor, int glMinor)
{
    Window *retval = (Window *)malloc(sizeof(Window));

    retval->width = width;
    retval->height = height;
    retval->gl_major_ver = glMajor;
    retval->gl_minor_ver = glMinor;

    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, retval->gl_major_ver);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, retval->gl_minor_ver);

    retval->handle = glfwCreateWindow(retval->width, retval->height, name, NULL, NULL);

    assert(retval->handle != GLEW_OK);

    glfwMakeContextCurrent(retval->handle);

    assert(glewInit() == 0);

    return retval;
}

void destroy_window(Window *window)
{
    glfwDestroyWindow(window->handle);
    free(window);
}
