#ifndef QUAT_H
#define QUAT_H

#include "math/mat4.h"
#include "math/vec3.h"

typedef struct {
  float x;
  float y;
  float z;
  float w;
} quat;

quat quat_create(float w, float x, float y, float z);
quat quat_rotate(quat q, float angle, vec3 axis);
quat quat_conjugate(quat q);
quat quat_normalize(quat q);
quat quat_multiply(quat q_a, quat q_b);
quat quat_multiply_by_vec3(quat q, vec3 vec);
quat euler_to_quat(float yaw, float pitch, float roll);
vec3 quat_to_euler(quat q);
quat quat_lookat(vec3 source, vec3 destination, vec3 position, vec3 target, vec3 up);
mat4 quat_to_mat4(quat q);
quat axisangle_to_quat(float angle, vec3 axis);

#endif /* QUAT_H */
