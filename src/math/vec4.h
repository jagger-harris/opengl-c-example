#ifndef VEC4_H
#define VEC4_H

typedef struct vec4 {
  float x;
  float y;
  float z;
  float w;
} vec4;

vec4 vec4_create_same_values(float values);
vec4 vec4_create_from_values(float x, float y, float z, float w);
float vec4_dot(vec4 vec3_a, vec4 vec3_b);

#endif /* VEC4_H */
