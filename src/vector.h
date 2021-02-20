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

typedef struct
{
    float x;
    float y;
    float z;
    float a;

} vec4;

vec2 vec2_add(vec2 v1, vec2 v2);
vec3 vec3_add(vec3 v1, vec3 v2);

vec2 vec2_subtract(vec2 v1, vec2 v2);
vec3 vec3_subtract(vec3 v1, vec3 v2);

float vec2_dot(vec2 v1, vec2 v2);
float vec3_dot(vec3 v1, vec3 v2);

vec2 vec2_scale(float scalar, vec2 v);
vec3 vec3_scale(float scalar, vec3 v);

float vec2_magnitude(vec2 v);
float vec3_magnitude(vec3 v);

static inline vec2 vec2_create(float x, float y)
{
    vec2 vector = {x, y};
    return vector;
}

static inline vec3 vec3_create(float x, float y, float z)
{
    vec3 vector = {x, y, z};
    return vector;
}

static inline vec4 vec4_create(float x, float y, float z, float a)
{
    vec4 vector = {x, y, z, a};
    return vector;
}

#endif
