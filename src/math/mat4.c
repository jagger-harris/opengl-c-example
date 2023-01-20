#include "mat4.h"
#include "math/vec4.h"
#include <math/math.h>

#include <assert.h>
#include <math.h>
#include <stdio.h>

void mat4_print(mat4 mat4) {
  vec4 col1 = vec4_create_from_values(mat4.values[0], mat4.values[4],
                                      mat4.values[8], mat4.values[12]);
  vec4 col2 = vec4_create_from_values(mat4.values[1], mat4.values[5],
                                      mat4.values[9], mat4.values[13]);
  vec4 col3 = vec4_create_from_values(mat4.values[2], mat4.values[6],
                                      mat4.values[10], mat4.values[14]);
  vec4 col4 = vec4_create_from_values(mat4.values[3], mat4.values[7],
                                      mat4.values[11], mat4.values[15]);

  printf("%f %f %f %f\n", col1.x, col1.y, col1.z, col1.w);
  printf("%f %f %f %f\n", col2.x, col2.y, col2.z, col2.w);
  printf("%f %f %f %f\n", col3.x, col3.y, col3.z, col3.w);
  printf("%f %f %f %f\n", col4.x, col4.y, col4.z, col4.w);
  printf("\n");
}

mat4 mat4_create_from_values(float values[MAT4_SIZE]) {
  mat4 mat4;

  for (int i = 0; i < MAT4_SIZE; i++) {
    mat4.values[i] = values[i];
  }

  return mat4;
}

mat4 mat4_create_same_value(float value) {
  mat4 mat4;

  for (int i = 0; i < MAT4_SIZE; i++) {
    mat4.values[i] = value;
  }

  return mat4;
}

mat4 mat4_create_identity() {
  mat4 mat4 = mat4_create_same_value(0.0f);

  mat4.values[0] = 1.0f;
  mat4.values[5] = 1.0f;
  mat4.values[10] = 1.0f;
  mat4.values[15] = 1.0f;

  return mat4;
}

mat4 mat4_multiply(mat4 mat4_a, mat4 mat4_b) {
  mat4 mat4;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat4.values[i * 4 + j] =
          mat4_a.values[0 * 4 + j] * mat4_b.values[i * 4 + 0] +
          mat4_a.values[1 * 4 + j] * mat4_b.values[i * 4 + 1] +
          mat4_a.values[2 * 4 + j] * mat4_b.values[i * 4 + 2] +
          mat4_a.values[3 * 4 + j] * mat4_b.values[i * 4 + 3];
    }
  }

  return mat4;
}

mat4 mat4_scale(mat4 transform, vec3 scale) {
  mat4 transform_scale = mat4_create_same_value(0.0f);

  /* Set scale */
  transform_scale.values[0] = scale.x;
  transform_scale.values[5] = scale.y;
  transform_scale.values[10] = scale.z;
  transform_scale.values[15] = 1.0f;

  transform = mat4_multiply(transform, transform_scale);

  return transform_scale;
}

mat4 mat4_translate(mat4 transform, vec3 translate) {
  mat4 transform_translate = mat4_create_identity();

  /* Set translation */
  transform_translate.values[12] = translate.x;
  transform_translate.values[13] = translate.y;
  transform_translate.values[14] = translate.z;

  transform = mat4_multiply(transform, transform_translate);

  return transform;
}

mat4 mat4_rotate(mat4 transform, float angle, vec3 axis) {
  mat4 transform_rotate;
  float x;
  float y;
  float z;
  float s_angle = sin(angle);
  float c_angle = cos(angle);

  vec3 axis_normal = vec3_normalize(axis);
  x = axis_normal.x;
  y = axis_normal.y;
  z = axis_normal.z;

  /* Rotation equations */
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

  transform = mat4_multiply(transform, transform_rotate);

  return transform;
}

mat4 mat4_orthographic(float near_plane, float far_plane) {
  mat4 orthographic = mat4_create_same_value(0.0f);

  return orthographic;
}

mat4 mat4_perspective(float field_of_view, float aspect_ratio, float near_plane,
                      float far_plane) {
  mat4 perspective = mat4_create_same_value(0.0f);
  float top = near_plane * tanf((PI / 180.0f) * (field_of_view * 0.5));
  float bottom = -top;
  float right = top * aspect_ratio;
  float left = -right;

  perspective.values[0] = (2 * near_plane) / (right - left);
  perspective.values[5] = (2 * near_plane) / (top - bottom);
  perspective.values[8] = (right + left) / (right - left);
  perspective.values[9] = (top + bottom) / (top - bottom);
  perspective.values[10] =
      -((far_plane + near_plane) / (far_plane - near_plane));
  perspective.values[11] = -1;
  perspective.values[14] =
      -((2 * far_plane * near_plane) / (far_plane - near_plane));

  return perspective;
}

mat4 mat4_lookat(vec3 position, vec3 target, vec3 up) {
  mat4 lookat = mat4_create_identity();
  vec3 z_axis = vec3_normalize(vec3_subtract(target, position));
  vec3 x_axis = vec3_normalize(vec3_cross(z_axis, up));
  vec3 y_axis = vec3_cross(x_axis, z_axis);

  z_axis = vec3_negate(z_axis);

  lookat.values[0] = x_axis.x;
  lookat.values[1] = y_axis.x;
  lookat.values[2] = z_axis.x;
  lookat.values[4] = x_axis.y;
  lookat.values[5] = y_axis.y;
  lookat.values[6] = z_axis.y;
  lookat.values[8] = x_axis.z;
  lookat.values[9] = y_axis.z;
  lookat.values[10] = z_axis.z;
  lookat.values[12] = -vec3_dot(x_axis, position);
  lookat.values[13] = -vec3_dot(y_axis, position);
  lookat.values[14] = -vec3_dot(z_axis, position);

  return lookat;
}