#ifndef WININ_H
#define WININ_H

#define GLFW_INCLUDE_NONE
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

typedef struct
{
    GLFWwindow *handle;
    int width;
    int height;
    int gl_major_ver;
    int gl_minor_ver;
} Window;

Window *create_window(const char *name, int width, int height, int glMajor, int glMinor);
inline void swap_buffers(Window *window) { glfwSwapBuffers(window->handle); }
void handle_input();
void destroy_window(Window *window);
#endif
