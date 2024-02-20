#include "vec4.h"

vec4 vec4_create_same_values(float values) {
  vec4 vec4;

  vec4.x = values;
  vec4.y = values;
  vec4.z = values;
  vec4.w = values;

  return vec4;
}

vec4 vec4_create_from_values(float x, float y, float z, float w) {
  vec4 vec4;

  vec4.x = x;
  vec4.y = y;
  vec4.z = z;
  vec4.w = w;

  return vec4;
}

float vec4_dot(vec4 *vec4_a, vec4 *vec4_b) {
  float dot;

  dot = (vec4_a->x * vec4_b->x) + (vec4_a->y * vec4_b->y) +
        (vec4_a->z * vec4_b->z) + (vec4_a->w * vec4_b->w);

  return dot;
}
