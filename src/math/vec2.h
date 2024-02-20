#ifndef VEC2_H
#define VEC2_H

typedef struct vec2 {
  float x;
  float y;
} vec2;

vec2 vec2_create_same_values(float values);
vec2 vec2_create_from_values(float x, float y);
vec2 vec2_add(vec2 *vec2_a, vec2 *vec2_b);
vec2 vec2_subtract(vec2 *vec2_a, vec2 *vec2_b);
vec2 vec2_negate(vec2 *vec2_a);
vec2 vec2_multiply_num_on_vec2(float num, vec2 *vec2_a);
vec2 vec2_normalize(vec2 *vec2_a);
float vec2_dot(vec2 *vec2_a, vec2 *vec2_b);

#endif /* VEC2_H */
