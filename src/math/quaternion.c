#include "quaternion.h"
#include "math.h"

#include <math.h>

quat quat_create(float w, float x, float y, float z) {
  quat quat;

  quat.w = w;
  quat.x = x;
  quat.y = y;
  quat.z = z;

  return quat;
}

quat quat_rotate(quat q, float angle, vec3 axis) {
  quat q_rotate;
  float half_angle = angle * 0.5;

  q_rotate.w = cos(half_angle);
  q_rotate.x = axis.x * sin(half_angle);
  q_rotate.y = axis.y * sin(half_angle);
  q_rotate.z = axis.z * sin(half_angle);

  return q_rotate;
}

quat quat_conjugate(quat q) {
  quat q_conjugate;

  q_conjugate.w = q.w;
  q_conjugate.x = -q.x;
  q_conjugate.y = -q.y;
  q_conjugate.z = -q.z;

  return q_conjugate;
}

quat quat_normalize(quat q) {
  quat q_normalized = q;
  float x = q.x;
  float y = q.y;
  float z = q.z;
  float w = q.w;
  float length = sqrt(x * x + y * y + z * z + w * w);

  q_normalized.x /= length;
  q_normalized.y /= length;
  q_normalized.z /= length;
  q_normalized.w /= length;

  return q_normalized;
}

quat quat_multiply(quat q_a, quat q_b) {
  quat quat;
  float x = q_a.x * q_b.w + q_a.w * q_b.x + q_a.y * q_b.z - q_a.z * q_b.y;
  float y = q_a.y * q_b.w + q_a.w * q_b.y + q_a.z * q_b.x - q_a.x * q_b.z;
  float z = q_a.z * q_b.w + q_a.w * q_b.z + q_a.x * q_b.y - q_a.y * q_b.x;
  float w = q_a.w * q_b.w - q_a.x * q_b.x - q_a.y * q_b.y - q_a.z * q_b.z;

  quat.x = x;
  quat.y = y;
  quat.z = z;
  quat.w = w;

  return quat;
}

quat quat_multiply_by_vec3(quat q, vec3 vec) {
  quat quat;
  float x = q.w * vec.x + q.y * vec.z - q.z * vec.y;
  float y = q.w * vec.y + q.z * vec.x - q.x * vec.z;
  float z = q.w * vec.z + q.x * vec.y - q.y * vec.x;
  float w = -q.x * vec.x - q.y * vec.y - q.z * vec.z;

  quat.x = x;
  quat.y = y;
  quat.z = z;
  quat.w = w;

  return quat;
}

quat euler_to_quat(float yaw, float pitch, float roll) {
  quat quat;
  float c_yaw = cos(yaw * 0.5);
  float s_yaw = sin(yaw * 0.5);
  float c_pitch = cos(pitch * 0.5);
  float s_pitch = sin(pitch * 0.5);
  float c_roll = cos(roll * 0.5);
  float s_roll = sin(roll * 0.5);

  quat.w = c_yaw * c_pitch * c_roll + s_yaw * s_pitch * s_roll;
  quat.x = c_yaw * c_pitch * s_roll - s_yaw * s_pitch * c_roll;
  quat.y = c_yaw * s_pitch * c_roll + s_yaw * c_pitch * s_roll;
  quat.z = s_yaw * c_pitch * c_roll - c_yaw * s_pitch * s_roll;

  return quat;
}

vec3 quat_to_euler(quat q) {
  vec3 euler;
  float sin_yaw = 2 * (q.w * q.z + q.x * q.y);
  float cos_yaw = 1 - 2 * (q.y * q.y + q.z * q.z);
  float sin_pitch = sqrtf(1 + 2 * (q.w * q.y - q.x * q.z));
  float cos_pitch = sqrtf(1 - 2 * (q.w * q.y - q.x * q.z));
  float sin_roll = 2 * (q.w * q.x + q.y * q.z);
  float cos_roll = 1 - 2 * (q.x * q.x + q.y * q.y);

  euler.x = atan2f(sin_yaw, cos_yaw);
  euler.y = atan2f(sin_pitch, cos_pitch) - PI * 0.5;
  euler.z = atan2f(sin_roll, cos_roll);

  return euler;
}

mat4 quat_to_mat4(quat q) {
  mat4 mat4;

  float x = q.x;
  float y = q.y;
  float z = q.z;
  float w = q.w;

  mat4.values[0] = 1 - 2 * (y * y) - 2 * (z * z);
  mat4.values[1] = 2 * x * y + 2 * w * z;
  mat4.values[2] = 2 * x * z - 2 * w * y;
  mat4.values[3] = 0;
  mat4.values[4] = 2 * x * y - 2 * w * z;
  mat4.values[5] = 1 - 2 * (x * x) - 2 * (z * z);
  mat4.values[6] = 2 * y * z + 2 * w * x;
  mat4.values[7] = 0;
  mat4.values[8] = 2 * x * z + 2 * w * y;
  mat4.values[9] = 2 * y * z - 2 * w * x;
  mat4.values[10] = 1 - 2 * (x * x) - 2 * (y * y);
  mat4.values[11] = 0;
  mat4.values[12] = 0;
  mat4.values[13] = 0;
  mat4.values[14] = 0;
  mat4.values[15] = 1;

  return mat4;
}

quat axisangle_to_quat(float angle, vec3 axis) {
  quat quat;
  float s_half_angle = sin(angle * 0.5);
  float c_half_angle = cos(angle * 0.5);

  quat.x = axis.x * s_half_angle;
  quat.y = axis.y * s_half_angle;
  quat.z = axis.z * s_half_angle;
  quat.w = c_half_angle;

  return quat;
}
