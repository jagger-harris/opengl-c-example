#ifndef QUAT_H
#define QUAT_H

#include "mat4.h"
#include "vec3.h"

typedef struct {
  float x;
  float y;
  float z;
  float w;
} quat;

quat quat_create(float w, float x, float y, float z);
quat quat_create_from_axis_angle(vec3 *axis, float angle);
quat quat_conjugate(quat *quat_a);
quat quat_normalize(quat *quat_a);
quat quat_multiply(quat *quat_a, quat *quat_b);
quat quat_multiply_by_vec3(quat *quat_a, vec3 *vec3_a);
quat euler_to_quat(float yaw, float pitch, float roll);
vec3 quat_to_euler(quat *quat_a);
mat4 quat_to_mat4(quat *quat_a);
quat axis_angle_to_quat(vec3 *axis, float angle);

#endif /* QUAT_H */
