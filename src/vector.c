#include "vector.h"

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

vec2 vec2_multiply(vec2 v1, vec2 v2)
{
    vec2 retval;
    retval.x = v1.x * v2.x;
    retval.y = v1.y * v2.y;
    return retval;
}

vec3 vec3_multiply(vec3 v1, vec3 v2)
{
    vec3 retval;
    retval.x = v1.x * v2.x;
    retval.y = v1.y * v2.y;
    retval.z = v1.z * v2.z;
    return retval;
}
