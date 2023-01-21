#include "camera.h"

#include "math/math.h"

#include <math.h>

void camera_update(camera *camera);

camera *camera_create(float pos_x, float pos_y, float pos_z, float yaw,
                      float pitch, float speed, float sensitivity,
                      float scr_width, float scr_height) {
  camera *camera = malloc(sizeof(*camera));

  camera->position = vec3_create_from_values(pos_x, pos_y, pos_z);
  camera->target = vec3_create_from_values(0.0f, 0.0f, -1.0f);
  camera->up = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  camera->up_world = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  camera->yaw = yaw;
  camera->pitch = pitch;
  camera->speed = speed;
  camera->sensitivity = sensitivity;
  camera->last_x = scr_width * 0.5;
  camera->last_y = scr_height * 0.5;

  camera_update(camera);

  return camera;
}

void camera_destroy(camera *camera) { free(camera); }

mat4 camera_lookat(camera *camera) {
  return mat4_lookat(camera->position,
                     vec3_add(camera->position, camera->target), camera->up);
}

void camera_keyboard_input(camera *camera, direction direction,
                           float velocity) {
  if (direction == FORWARD) {
    camera->position = vec3_add(
        camera->position, vec3_multiply_num_on_vec3(velocity, camera->target));
  }

  if (direction == BACKWARD) {
    camera->position = vec3_subtract(
        camera->position, vec3_multiply_num_on_vec3(velocity, camera->target));
  }

  if (direction == LEFT) {
    camera->position = vec3_subtract(
        camera->position, vec3_multiply_num_on_vec3(velocity, camera->right));
  }

  if (direction == RIGHT) {
    camera->position = vec3_add(
        camera->position, vec3_multiply_num_on_vec3(velocity, camera->right));
  }
}

void camera_mouse_input(camera *camera, float offset_x, float offset_y) {
  offset_x *= camera->sensitivity;
  offset_y *= camera->sensitivity;

  camera->yaw += offset_x;
  camera->pitch += offset_y;

  if (camera->pitch > 89.0f) {
    camera->pitch = 89.0f;
  }

  if (camera->pitch < -89.0f) {
    camera->pitch = -89.0f;
  }

  camera_update(camera);
}

void camera_update(camera *camera) {
  vec3 target;
  target.x = cos(degs_to_rads(camera->yaw)) * cos(degs_to_rads(camera->pitch));
  target.y = sin(degs_to_rads(camera->pitch));
  target.z = sin(degs_to_rads(camera->yaw)) * cos(degs_to_rads(camera->pitch));
  camera->target = vec3_normalize(target);
  camera->right = vec3_normalize(vec3_cross(camera->target, camera->up_world));
  camera->up = vec3_normalize(vec3_cross(camera->right, camera->target));
}
