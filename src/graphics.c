#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

renderer_context *init_renderer(Window *win)
{
    renderer_context *context = (renderer_context *)malloc(sizeof(renderer_context));
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    context->context_shader = create_shader("./src/shaders/vertex.vs",
                                            "./src/shaders/fragment.vs");

    context->projection = mat4_ortho(0.0f, win->width, 0.0f, win->height, -1.0f, 1.0f);

    context->model = mat4_diagonal(1.0f);

    context->context_vb = create_vertexbuffer(vertices, sizeof(vertices));
    set_vertexbuffer_attibutes(&context->context_vb, 0, 3, 3 * sizeof(float), (void *)0);

    context->projLoc = glGetUniformLocation(context->context_shader.programID, "projection");
    context->modelLoc = glGetUniformLocation(context->context_shader.programID, "model");

    glUseProgram(context->context_shader.programID);
    glUniformMatrix4fv(context->projLoc, 1, GL_FALSE, &context->projection);
    glUniformMatrix4fv(context->modelLoc, 1, GL_FALSE, &context->model);
    return context;
}

renderer_context *destroy_renderer(renderer_context *renderer)
{
    glDeleteProgram(renderer->context_shader.programID);
    glDeleteBuffers(1, &renderer->context_vb.bufferID);
    free(renderer);
}

void draw_quad(renderer_context *context, const vec3 *position, float cube_size)
{
    glUseProgram(context->context_shader.programID);
    glBindBuffer(GL_ARRAY_BUFFER, context->context_vb.bufferID);

    mat4 temp = mat4_diagonal(1.0f);
    context->model = mat4_translate(&temp, position);

    vec3 scale_vector = {cube_size, cube_size, 0.0f};
    context->model = mat4_scale(&context->model, &scale_vector);

    glUniformMatrix4fv(context->modelLoc, 1, GL_FALSE, &context->model);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_colored_quad(renderer_context *context, vec3 position, vec3 color)
{
}

char *_load_file(const char *filepath)
{
    char *buffer;
    int size;
    FILE *file = fopen(filepath, "r");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
        buffer = (char *)malloc((sizeof(char) * size) + (sizeof(char) * 1));
        fread(buffer, sizeof(char), size, file);
        buffer[size] = '\0';
    }
    else
    {
        printf("File is not found: %s\n", filepath);
        exit(1);
    }

    fclose(file);
    return buffer;
}

shader create_shader(const char *vpath, const char *fpath)
{
    char *vsource = _load_file(vpath);
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vsource, NULL);
    glCompileShader(vshader);

    GLint success = 0;
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetShaderInfoLog(vshader, logSize, &logSize, &error_message[0]);
        glDeleteShader(vshader);
        printf("Error in %s: %s\n", vpath, error_message);
        exit(1);
    }

    char *fsource = _load_file(fpath);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fsource, NULL);
    glCompileShader(fshader);

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetShaderInfoLog(fshader, logSize, &logSize, &error_message[0]);
        printf("Error in %s:  %s\n", fpath, error_message);
        glDeleteShader(vshader);
        exit(1);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        GLchar *error_message = (GLchar *)malloc(sizeof(GLchar) * logSize);
        glGetProgramInfoLog(program, logSize, &logSize, error_message);
        printf("%s", error_message);
        glDeleteProgram(program);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        exit(1);
    }

    glDetachShader(program, vshader);
    glDetachShader(program, fshader);

    shader retval = {program};

    free(vsource);
    free(fsource);
    return retval;
}

vertexbuffer create_vertexbuffer(float *vertices, size_t bufferSize)
{
    vertexbuffer retval = {0};
    retval.vertices = vertices;
    retval.buffer_size = bufferSize;
    glGenBuffers(1, &retval.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, retval.bufferID);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);
    return retval;
}

void set_vertexbuffer_attibutes(vertexbuffer *vb, int index, size_t size, size_t stride, void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vb->bufferID);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          pointer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
