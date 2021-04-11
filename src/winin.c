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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    retval->handle = glfwCreateWindow(retval->width, retval->height, name, NULL, NULL);

    assert(retval->handle != GLEW_OK);

    glfwMakeContextCurrent(retval->handle);
    glfwSetKeyCallback(retval->handle, key_callback);

    assert(glewInit() == 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return retval;
}

void destroy_window(Window *window)
{
    glfwDestroyWindow(window->handle);
    free(window);
}

typedef struct
{
    int key_code;
    int is_pressed;
} KeyPair;

static KeyPair keyboard_inputs[] = {
    {GLFW_KEY_0, 0},
    {GLFW_KEY_1, 0},
    {GLFW_KEY_2, 0},
    {GLFW_KEY_3, 0},
    {GLFW_KEY_4, 0},
    {GLFW_KEY_5, 0},
    {GLFW_KEY_6, 0},
    {GLFW_KEY_7, 0},
    {GLFW_KEY_8, 0},
    {GLFW_KEY_9, 0},
    {GLFW_KEY_A, 0},
    {GLFW_KEY_B, 0},
    {GLFW_KEY_C, 0},
    {GLFW_KEY_D, 0},
    {GLFW_KEY_E, 0},
    {GLFW_KEY_F, 0},
    {GLFW_KEY_G, 0},
    {GLFW_KEY_H, 0},
    {GLFW_KEY_I, 0},
    {GLFW_KEY_J, 0},
    {GLFW_KEY_K, 0},
    {GLFW_KEY_L, 0},
    {GLFW_KEY_M, 0},
    {GLFW_KEY_N, 0},
    {GLFW_KEY_O, 0},
    {GLFW_KEY_P, 0},
    {GLFW_KEY_Q, 0},
    {GLFW_KEY_R, 0},
    {GLFW_KEY_S, 0},
    {GLFW_KEY_T, 0},
    {GLFW_KEY_U, 0},
    {GLFW_KEY_V, 0},
    {GLFW_KEY_W, 0},
    {GLFW_KEY_X, 0},
    {GLFW_KEY_Y, 0},
    {GLFW_KEY_Z, 0},
};

void set_key_lookup_table(int keycode, int ispressed)
{
    for (unsigned long int i = 0; i < sizeof(keyboard_inputs) / sizeof(KeyPair); ++i)
        if (keyboard_inputs[i].key_code == keycode)
            keyboard_inputs[i].is_pressed = ispressed;
}

int get_key_down(int keycode)
{
    int retval = 0;
    for (unsigned long int i = 0; i < sizeof(keyboard_inputs) / sizeof(KeyPair); ++i)
        if (keyboard_inputs[i].key_code == keycode)
        {
            retval = keyboard_inputs[i].is_pressed;
            keyboard_inputs[i].is_pressed = 0;
        }
    return retval;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        set_key_lookup_table(key, 1);
}

void fill_screen_with_color(float r, float g, float b, float a)
{
    float p1 = r / 255.0f;
    float p2 = g / 255.0f;
    float p3 = b / 255.0f;
    float p4 = a;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(p1, p2, p3, p4);
}
