#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    float values[4][4];
} mat4;

mat4 mat4_create(float value);
mat4 mat4_multiply(mat4 first, mat4 second);

mat4 mat4_ortho(float left, float right, float buttom, float top, float near, float far);

#endif
