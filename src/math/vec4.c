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

float vec4_dot(vec4 vec3_a, vec4 vec3_b) {
  float dot;

  dot = (vec3_a.x * vec3_b.x) + (vec3_a.y * vec3_b.y) + (vec3_a.z * vec3_b.z) +
        (vec3_a.w * vec3_b.w);

  return dot;
}
