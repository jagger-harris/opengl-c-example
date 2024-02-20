#include "vec2.h"
#include <math.h>

vec2 vec2_create_same_values(float values) {
  vec2 vec2;

  vec2.x = values;
  vec2.y = values;

  return vec2;
}

vec2 vec2_create_from_values(float x, float y) {
  vec2 vec2;

  vec2.x = x;
  vec2.y = y;

  return vec2;
}

vec2 vec2_add(vec2 *vec2_a, vec2 *vec2_b) {
  vec2 vec2_added;

  vec2_added.x = vec2_a->x + vec2_b->x;
  vec2_added.y = vec2_a->y + vec2_b->y;

  return vec2_added;
}

vec2 vec2_subtract(vec2 *vec2_a, vec2 *vec2_b) {
  vec2 vec2_subtracted;

  vec2_subtracted.x = vec2_a->x - vec2_b->x;
  vec2_subtracted.y = vec2_a->y - vec2_b->y;

  return vec2_subtracted;
}

vec2 vec2_negate(vec2 *vec2_a) {
  vec2 vec2_negated;

  vec2_negated.x = -vec2_a->x;
  vec2_negated.y = -vec2_a->y;

  return vec2_negated;
}

vec2 vec2_multiply_num_on_vec2(float num, vec2 *vec2_a) {
  vec2 vec2_multiplied;

  vec2_multiplied.x = num * vec2_a->x;
  vec2_multiplied.y = num * vec2_a->y;

  return vec2_multiplied;
}

vec2 vec2_normalize(vec2 *vec2_a) {
  vec2 vec2_normalized = *vec2_a;
  float x = vec2_a->x;
  float y = vec2_a->y;
  float length = sqrt(x * x + y * y);

  vec2_normalized.x /= length;
  vec2_normalized.y /= length;

  return vec2_normalized;
}

float vec2_dot(vec2 *vec2_a, vec2 *vec2_b) {
  float dot;

  dot = (vec2_a->x * vec2_b->x) + (vec2_a->y * vec2_b->y);

  return dot;
}
