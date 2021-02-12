#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    float x;
    float y;

} vec2;

typedef struct
{
    float x;
    float y;
    float z;

} vec3;

vec2 vec2_add(vec2 v1, vec2 v2);
vec3 vec3_add(vec3 v1, vec3 v2);

vec2 vec2_subtract(vec2 v1, vec2 v2);
vec3 vec3_subtract(vec3 v1, vec3 v2);

// Dot product
vec2 vec2_multiply(vec2 v1, vec2 v2);
vec3 vec3_multiply(vec3 v1, vec3 v2);

#endif
