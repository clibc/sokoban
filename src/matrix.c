#include "matrix.h"

mat4 mat4_diagonal(float value)
{
    // r * 4  + c
    mat4 retval = {0};
    retval.values[0 * 4 + 0] = value;
    retval.values[1 * 4 + 1] = value;
    retval.values[2 * 4 + 2] = value;
    retval.values[3 * 4 + 3] = value;

    return retval;
}

mat4 mat4_multiply(mat4 first, mat4 second)
{
    mat4 retval = {0};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            float sum = 0.0f;
            for (int r = 0; r < 4; ++r)
            {
                sum = first.values[r * 4 + j] * second.values[j * 4 + r];
            }
            retval.values[j * 4 + i] = sum;
        }
    }
    return retval;
}

mat4 mat4_ortho(float left, float right, float buttom, float top, float near, float far)
{
    mat4 retval = mat4_diagonal(1.0f);
    retval.values[0 * 4 + 0] = 2.0f / (right - left);
    retval.values[1 * 4 + 1] = 2.0f / (top - buttom);
    retval.values[2 * 4 + 2] = -2.0f / (far - near);
    retval.values[0 * 4 + 3] = -((right + left) / (right - left));
    retval.values[1 * 4 + 3] = -((top + buttom) / (top - buttom));
    retval.values[2 * 4 + 3] = -((far + near) / (far - near));

    return retval;
}

mat4 mat4_translate(mat4 matrix, vec3 vector)
{
    mat4 translation = mat4_diagonal(1.0f);
    translation.values[0 * 4 + 3] = vector.x;
    translation.values[1 * 4 + 3] = vector.y;
    translation.values[2 * 4 + 3] = vector.z;

    return translation;
}

mat4 mat4_scale(mat4 matrix, vec3 vector)
{
    mat4 retval = {0};
    mat4 scale = mat4_diagonal(1.0f);
    scale.values[0 * 4 + 0] = vector.x;
    scale.values[1 * 4 + 1] = vector.y;
    scale.values[2 * 4 + 2] = vector.z;

    retval = mat4_multiply(matrix, scale);
    return retval;
}

vec4 mat4_multiply_vec3(mat4 matrix, vec3 vector)
{
    vec4 retval = {0.0f};

    return retval;
}
