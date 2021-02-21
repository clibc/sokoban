#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct
{
    float values[16];
} mat4;

mat4 mat4_diagonal(float value);
mat4 mat4_multiply(const mat4 *first, const mat4 *second);
vec4 mat4_multiply_vec3(const mat4 *matrix, const vec3 *vector);
mat4 mat4_scale(const mat4 *matrix, const vec3 *vector);

mat4 mat4_ortho(float left, float right, float buttom, float top, float near, float far);

mat4 mat4_translate(const mat4 *matrix, const vec3 *vector);

mat4 mat4_rotate(float angle, const vec3 *vector);
#endif
