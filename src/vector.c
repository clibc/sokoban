#include "vector.h"
#include <math.h>

float v_sqrt(float number)
{
    // John Carmack's sqrt function
    int i;
    float x, y;
    x = number * 0.5f;
    y = number;
    i = *(int *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (x * y * y));
    y = y * (1.5f - (x * y * y));
    return number * y;
}

vec2 vec2_add(vec2 v1, vec2 v2)
{
    vec2 retval;
    retval.x = v1.x + v2.x;
    retval.y = v1.y + v2.y;
    return retval;
}

vec3 vec3_add(vec3 v1, vec3 v2)
{
    vec3 retval;
    retval.x = v1.x + v2.x;
    retval.y = v1.y + v2.y;
    retval.z = v1.z + v2.z;
    return retval;
}

vec2 vec2_subtract(vec2 v1, vec2 v2)
{
    vec2 retval;
    retval.x = v1.x - v2.x;
    retval.y = v1.y - v2.y;
    return retval;
}

vec3 vec3_subtract(vec3 v1, vec3 v2)
{
    vec3 retval;
    retval.x = v1.x - v2.x;
    retval.y = v1.y - v2.y;
    retval.z = v1.z - v2.z;
    return retval;
}

float vec2_dot(vec2 v1, vec2 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}
float vec3_dot(vec3 v1, vec3 v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec2 vec2_scale(float scalar, vec2 v)
{
    vec2 retval;
    retval.x = v.x * scalar;
    retval.y = v.y * scalar;
    return retval;
}

vec3 vec3_scale(float scalar, vec3 v)
{
    vec3 retval;
    retval.x = v.x * scalar;
    retval.y = v.y * scalar;
    retval.z = v.z * scalar;
    return retval;
}

float vec2_magnitude(vec2 v)
{
    return v_sqrt((v.x * v.x) + (v.y * v.y));
}

float vec3_magnitude(vec3 v)
{
    return v_sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
