#include "matrix.h"

mat4 mat4_create(float value)
{
    mat4 retval = {0.0f};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            retval.values[j][i] = value;
    }

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
    retval.values[0][3] = -((right + left) / (right - left));
    retval.values[1][3] = -((top + buttom) / (top - buttom));
    retval.values[2][3] = -((far + near) / (far - near));

    return retval;
}
