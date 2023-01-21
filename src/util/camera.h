#ifndef CAMERA_H
#define CAMERA_H

#include "math/mat4.h"
#include "math/vec3.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum direction { FORWARD, BACKWARD, LEFT, RIGHT } direction;

typedef struct camera {
  vec3 position;
  vec3 target;
  vec3 up;
  vec3 right;
  vec3 up_world;
  float yaw;
  float pitch;
  float speed;
  float sensitivity;
  float last_x;
  float last_y;
} camera;

camera *camera_create(float pos_x, float pos_y, float pos_z, float yaw,
                      float pitch, float speed, float sensitivity,
                      float scr_width, float scr_height);
void camera_destroy(camera *camera);
mat4 camera_lookat(camera *camera);
void camera_keyboard_input(camera *camera, direction direction, float velocity);
void camera_mouse_input(camera *camera, float offset_x, float offset_y);

#endif /* CAMERA_H */
