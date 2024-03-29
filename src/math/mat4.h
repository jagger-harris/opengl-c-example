#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"

#define MAT4_SIZE 16

typedef struct mat4 {
  float values[MAT4_SIZE];
} mat4;

void mat4_print(mat4 *mat4_a);
mat4 mat4_create_from_values(float values[MAT4_SIZE]);
mat4 mat4_create_same_value(float value);
mat4 mat4_create_identity(void);
mat4 mat4_multiply(mat4 *mat4_a, mat4 *mat4_b);
mat4 mat4_scale(mat4 *transform, vec3 *scale);
mat4 mat4_translate(mat4 *transform, vec3 *translate);
mat4 mat4_rotate(mat4 *transform, vec3 *axis, float angle);
mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane,
                      float far_plane);
mat4 mat4_orthographic(float left, float right, float bottom, float top,
                       float near_plane, float far_plane);
mat4 mat4_lookat(vec3 *position, vec3 *target, vec3 *up);

#endif /* MAT4_H */
