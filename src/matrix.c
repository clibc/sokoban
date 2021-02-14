#include "matrix.h"

mat4 mat4_diagonal(float value)
{
    mat4 retval = {0.0f};
    retval.values[0][0] = value;
    retval.values[1][1] = value;
    retval.values[2][2] = value;
    retval.values[3][3] = value;
    return retval;
}

mat4 mat4_multiply(mat4 first, mat4 second)
{
    mat4 retval = {0.0f};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            float sum = 0.0f;
            for (int m = 0; m < 4; ++m)
                sum += first.values[i][m] * second.values[m][j];

            retval.values[i][j] = sum;
        }
    }
    return retval;
}

mat4 mat4_ortho(float left, float right, float buttom, float top, float near, float far)
{
    mat4 retval = {1.0f};
    retval.values[0][0] = 2 / (right - left);
    retval.values[1][1] = 2 / (top - buttom);
    retval.values[2][2] = -2 / (far - near);
    retval.values[3][0] = -((right + left) / (right - left));
    retval.values[3][1] = -((top + buttom) / (top - buttom));
    retval.values[3][2] = -((far + near) / (far - near));

    return retval;
}

vec4 mat4_multiply_vec3(mat4 matrix, vec3 vector)
{
    vec4 retval = {0.0f};
    float multy[4] = {vector.x, vector.y, vector.z, 1.0f};

    for (int col = 0; col < 4; ++col)
    {
        float sum = 0.0f;
        for (int row = 0; row < 4; ++row)
        {
            for (int i = 0; i < 4; i++)
            {
                sum += matrix.values[col][row] * multy[i];
            }
            ((float *)&retval)[col] = sum;
        }
    }

    return retval;
}

mat4 mat4_translate(mat4 matrix, vec3 vector)
{
    matrix.values[3][0] = vector.x;
    matrix.values[3][1] = vector.y;
    matrix.values[3][2] = vector.z;
    return matrix;
}
