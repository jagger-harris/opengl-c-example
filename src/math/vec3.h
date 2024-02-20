#ifndef VEC3_H
#define VEC3_H

typedef struct vec3 {
  float x;
  float y;
  float z;
} vec3;

vec3 vec3_create_same_value(float value);
vec3 vec3_create_from_values(float x, float y, float z);
vec3 vec3_add(vec3 *vec3_a, vec3 *vec3_b);
vec3 vec3_subtract(vec3 *vec3_a, vec3 *vec3_b);
vec3 vec3_negate(vec3 *vec3_a);
vec3 vec3_multiply_num_on_vec3(float num, vec3 *vec3_a);
vec3 vec3_normalize(vec3 *vec3_a);
vec3 vec3_cross(vec3 *vec3_a, vec3 *vec3_b);
float vec3_dot(vec3 *vec3_a, vec3 *vec3_b);

#endif /* VEC3_H */
