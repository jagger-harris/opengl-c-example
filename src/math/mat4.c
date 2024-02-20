#include "mat4.h"
#include "math.h"
#include "vec4.h"
#include <math.h>
#include <stdio.h>

void mat4_print(mat4 *mat4_a) {
  vec4 col1 = vec4_create_from_values(mat4_a->values[0], mat4_a->values[4],
                                      mat4_a->values[8], mat4_a->values[12]);
  vec4 col2 = vec4_create_from_values(mat4_a->values[1], mat4_a->values[5],
                                      mat4_a->values[9], mat4_a->values[13]);
  vec4 col3 = vec4_create_from_values(mat4_a->values[2], mat4_a->values[6],
                                      mat4_a->values[10], mat4_a->values[14]);
  vec4 col4 = vec4_create_from_values(mat4_a->values[3], mat4_a->values[7],
                                      mat4_a->values[11], mat4_a->values[15]);

  printf("%f %f %f %f\n", col1.x, col1.y, col1.z, col1.w);
  printf("%f %f %f %f\n", col2.x, col2.y, col2.z, col2.w);
  printf("%f %f %f %f\n", col3.x, col3.y, col3.z, col3.w);
  printf("%f %f %f %f\n", col4.x, col4.y, col4.z, col4.w);
  printf("\n");
}

mat4 mat4_create_from_values(float values[MAT4_SIZE]) {
  mat4 mat4;
  size_t i;

  for (i = 0; i < MAT4_SIZE; i++) {
    mat4.values[i] = values[i];
  }

  return mat4;
}

mat4 mat4_create_same_value(float value) {
  mat4 mat4;
  size_t i;

  for (i = 0; i < MAT4_SIZE; i++) {
    mat4.values[i] = value;
  }

  return mat4;
}

mat4 mat4_create_identity(void) {
  mat4 mat4 = mat4_create_same_value(0.0f);

  mat4.values[0] = 1.0f;
  mat4.values[5] = 1.0f;
  mat4.values[10] = 1.0f;
  mat4.values[15] = 1.0f;

  return mat4;
}

mat4 mat4_multiply(mat4 *mat4_a, mat4 *mat4_b) {
  mat4 mat4;
  size_t row;
  size_t column;

  for (row = 0; row < 4; row++) {
    for (column = 0; column < 4; column++) {
      mat4.values[row * 4 + column] =
          mat4_a->values[0 * 4 + column] * mat4_b->values[row * 4 + 0] +
          mat4_a->values[1 * 4 + column] * mat4_b->values[row * 4 + 1] +
          mat4_a->values[2 * 4 + column] * mat4_b->values[row * 4 + 2] +
          mat4_a->values[3 * 4 + column] * mat4_b->values[row * 4 + 3];
    }
  }

  return mat4;
}

mat4 mat4_scale(mat4 *transform, vec3 *scale) {
  mat4 transform_scale = mat4_create_identity();

  transform_scale.values[0] = scale->x;
  transform_scale.values[5] = scale->y;
  transform_scale.values[10] = scale->z;
  transform_scale.values[15] = 1.0f;

  transform_scale = mat4_multiply(transform, &transform_scale);

  return transform_scale;
}

mat4 mat4_translate(mat4 *transform, vec3 *translate) {
  mat4 transform_translate = mat4_create_identity();

  transform_translate.values[12] = translate->x;
  transform_translate.values[13] = translate->y;
  transform_translate.values[14] = translate->z;

  transform_translate = mat4_multiply(transform, &transform_translate);

  return transform_translate;
}

mat4 mat4_rotate(mat4 *transform, vec3 *axis, float angle) {
  mat4 transform_rotate;
  vec3 axis_normal = vec3_normalize(axis);
  float x = axis_normal.x;
  float y = axis_normal.y;
  float z = axis_normal.z;
  float s_angle = sin(angle);
  float c_angle = cos(angle);

  transform_rotate.values[0] = c_angle + x * x * (1 - c_angle);
  transform_rotate.values[1] = y * x * (1 - c_angle) + z * s_angle;
  transform_rotate.values[2] = z * x * (1 - c_angle) - y * s_angle;
  transform_rotate.values[3] = 0.0f;
  transform_rotate.values[4] = x * y * (1 - c_angle) - z * s_angle;
  transform_rotate.values[5] = c_angle + y * y * (1 - c_angle);
  transform_rotate.values[6] = z * y * (1 - c_angle) + x * s_angle;
  transform_rotate.values[7] = 0.0f;
  transform_rotate.values[8] = x * z * (1 - c_angle) + y * s_angle;
  transform_rotate.values[9] = y * z * (1 - c_angle) - x * s_angle;
  transform_rotate.values[10] = c_angle + z * z * (1 - c_angle);
  transform_rotate.values[11] = 0.0f;
  transform_rotate.values[12] = 0.0f;
  transform_rotate.values[13] = 0.0f;
  transform_rotate.values[14] = 0.0f;
  transform_rotate.values[15] = 1.0f;

  transform_rotate = mat4_multiply(transform, &transform_rotate);

  return transform_rotate;
}

mat4 mat4_orthographic(float left, float right, float bottom, float top,
                       float near_plane, float far_plane) {
  mat4 orthographic = mat4_create_same_value(0.0f);

  orthographic.values[0] = 2.0f / (right - left);
  orthographic.values[5] = 2.0f / (top - bottom);
  orthographic.values[10] = -2.0f / (far_plane - near_plane);
  orthographic.values[12] = -(right + left) / (right - left);
  orthographic.values[13] = -(top + bottom) / (top - bottom);
  orthographic.values[14] =
      -(far_plane + near_plane) / (far_plane - near_plane);
  orthographic.values[15] = 1.0f;

  return orthographic;
}

mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane,
                      float far_plane) {
  mat4 perspective = mat4_create_same_value(0.0f);
  float top = near_plane * tanf((PI / 180.0f) * (fov * 0.5f));
  float bottom = -top;
  float right = top * aspect_ratio;
  float left = -right;

  perspective.values[0] = (2.0f * near_plane) / (right - left);
  perspective.values[5] = (2.0f * near_plane) / (top - bottom);
  perspective.values[8] = (right + left) / (right - left);
  perspective.values[9] = (top + bottom) / (top - bottom);
  perspective.values[10] =
      -((far_plane + near_plane) / (far_plane - near_plane));
  perspective.values[11] = -1.0f;
  perspective.values[14] =
      -((2.0f * far_plane * near_plane) / (far_plane - near_plane));

  return perspective;
}

mat4 mat4_lookat(vec3 *position, vec3 *target, vec3 *up) {
  mat4 lookat = mat4_create_identity();
  vec3 subtracted = vec3_subtract(target, position);
  vec3 z_axis = vec3_normalize(&subtracted);
  vec3 crossed = vec3_cross(&z_axis, up);
  vec3 x_axis = vec3_normalize(&crossed);
  vec3 y_axis = vec3_cross(&x_axis, &z_axis);

  z_axis = vec3_negate(&z_axis);

  lookat.values[0] = x_axis.x;
  lookat.values[1] = y_axis.x;
  lookat.values[2] = z_axis.x;
  lookat.values[4] = x_axis.y;
  lookat.values[5] = y_axis.y;
  lookat.values[6] = z_axis.y;
  lookat.values[8] = x_axis.z;
  lookat.values[9] = y_axis.z;
  lookat.values[10] = z_axis.z;
  lookat.values[12] = -vec3_dot(&x_axis, position);
  lookat.values[13] = -vec3_dot(&y_axis, position);
  lookat.values[14] = -vec3_dot(&z_axis, position);

  return lookat;
}
