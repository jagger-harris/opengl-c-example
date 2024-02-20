#ifndef CAMERA_H
#define CAMERA_H

#include "../math/mat4.h"
#include "../math/vec3.h"
#include <GLFW/glfw3.h>

typedef struct camera {
  mat4 view;
  mat4 projection;
  vec3 position;
  vec3 right;
  vec3 front;
  vec3 up;
  vec3 up_world;
  float yaw;
  float pitch;
  float speed;
  float sensitivity;
  float fov;
  float aspect_ratio;
  float near_plane;
  float far_plane;
} camera;

camera camera_create(float pos_x, float pos_y, float pos_z, float width, float height);
void camera_update_vectors(camera* camera);
void camera_update_projection(camera *camera);
void camera_process_key_input(camera* camera, GLFWwindow *window, float delta_time);
void camera_process_mouse_movement(camera* camera, float x_offset, float y_offset);
void camera_process_mouse_scroll(camera* camera, float y_offset);

#endif /* CAMERA_H */
