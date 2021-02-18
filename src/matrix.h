#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct
{
    float values[16];
} mat4;

mat4 mat4_diagonal(float value);
mat4 mat4_multiply(mat4 first, mat4 second);
vec4 mat4_multiply_vec3(mat4 matrix, vec3 vector);
mat4 mat4_scale(mat4 matrix, vec3 vector);

mat4 mat4_ortho(float left, float right, float buttom, float top, float near, float far);

mat4 mat4_translate(mat4 matrix, vec3 vector);

#endif
