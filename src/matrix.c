#include "matrix.h"

#include <math.h>

// c * 4  + r
mat4 mat4_diagonal(float value)
{
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
                sum += first.values[r * 4 + j] * second.values[i * 4 + r];
            }
            retval.values[i * 4 + j] = sum;
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
    retval.values[3 * 4 + 0] = -((right + left) / (right - left));
    retval.values[3 * 4 + 1] = -((top + buttom) / (top - buttom));
    retval.values[3 * 4 + 2] = -((far + near) / (far - near));

    return retval;
}

mat4 mat4_translate(mat4 matrix, vec3 vector)
{
    mat4 translation = mat4_diagonal(1.0f);
    translation.values[3 * 4 + 0] = vector.x;
    translation.values[3 * 4 + 1] = vector.y;
    translation.values[3 * 4 + 2] = vector.z;

    return translation;
}

mat4 mat4_scale(mat4 matrix, vec3 vector)
{
    mat4 scale = matrix;
    scale.values[0 * 4 + 0] = vector.x;
    scale.values[1 * 4 + 1] = vector.y;
    scale.values[2 * 4 + 2] = vector.z;

    return scale;
}

mat4 mat4_rotate(float angle, vec3 vector)
{
    mat4 result = mat4_diagonal(1.0f);

    float r = angle * (M_PI / 180.0f);
    float c = cos(r);
    float s = sin(r);
    float omc = 1.0f - c;

    float x = vector.x;
    float y = vector.y;
    float z = vector.z;

    result.values[0 + 0 * 4] = x * omc + c;
    result.values[1 + 0 * 4] = y * x * omc + z * s;
    result.values[2 + 0 * 4] = x * z * omc - y * s;

    result.values[0 + 1 * 4] = x * y * omc - z * s;
    result.values[1 + 1 * 4] = y * omc + c;
    result.values[2 + 1 * 4] = y * z * omc + x * s;

    result.values[0 + 2 * 4] = x * z * omc + y * s;
    result.values[1 + 2 * 4] = y * z * omc - x * s;
    result.values[2 + 2 * 4] = z * omc + c;

    return result;
}

vec4 mat4_multiply_vec3(mat4 matrix, vec3 vector)
{
    vec4 retval = {0.0f};
    retval.a = 1.0f;
    float *temp = (float *)&retval;

    for (int i = 0; i < 4; ++i)
    {
        float sum = 0;
        sum += matrix.values[i * 4 + 0] * vector.x;
        sum += matrix.values[i * 4 + 1] * vector.y;
        sum += matrix.values[i * 4 + 2] * vector.z;
        sum += matrix.values[i * 4 + 3];

        temp[i] = sum;
    }

    return retval;
}
