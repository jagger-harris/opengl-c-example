#include "camera.h"
#include "../math/math.h"
#include "GLFW/glfw3.h"
#include <math.h>

void camera_update_vectors(camera *camera) {
  vec3 front;
  vec3 right;
  vec3 up;

  front.x = cos(degs_to_rads(camera->yaw)) * cos(degs_to_rads(camera->pitch));
  front.y = sin(degs_to_rads(camera->pitch));
  front.z = sin(degs_to_rads(camera->yaw)) * cos(degs_to_rads(camera->pitch));

  camera->front = vec3_normalize(&front);
  right = vec3_cross(&camera->front, &camera->up_world);
  camera->right = vec3_normalize(&right);
  up = vec3_cross(&camera->right, &camera->front);
  camera->up = vec3_normalize(&up);
}

void camera_update_projection(camera *camera) {
  vec3 view = vec3_add(&camera->position, &camera->front);
  camera->view = mat4_lookat(&camera->position, &view, &camera->up);
  camera->projection = mat4_perspective(camera->fov, camera->aspect_ratio,
                                        camera->near_plane, camera->far_plane);
}

camera camera_create(float pos_x, float pos_y, float pos_z, float width,
                     float height) {
  camera camera;

  camera.position = vec3_create_from_values(pos_x, pos_y, pos_z);
  camera.front = vec3_create_from_values(0.0f, 0.0f, -1.0f);
  camera.up = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  camera.up_world = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  camera.yaw = -90.0f;
  camera.pitch = 0.0f;
  camera.speed = 2.5f;
  camera.sensitivity = 0.1f;
  camera.fov = 45.0f;
  camera.aspect_ratio = width / height;
  camera.near_plane = 0.1f;
  camera.far_plane = 1000.0f;

  camera_update_vectors(&camera);

  return camera;
}

void camera_process_key_input(camera *camera, GLFWwindow *window,
                              float delta_time) {
  vec3 velocity;
  float speed = camera->speed * delta_time;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    velocity = vec3_multiply_num_on_vec3(speed, &camera->front);
    camera->position = vec3_add(&camera->position, &velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    velocity = vec3_multiply_num_on_vec3(speed, &camera->front);
    camera->position = vec3_subtract(&camera->position, &velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    velocity = vec3_multiply_num_on_vec3(speed, &camera->right);
    camera->position = vec3_subtract(&camera->position, &velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    velocity = vec3_multiply_num_on_vec3(speed, &camera->right);
    camera->position = vec3_add(&camera->position, &velocity);
  }
}

void camera_process_mouse_movement(camera *camera, float offset_x,
                                   float offset_y) {
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

  camera_update_vectors(camera);
}

void camera_process_mouse_scroll(camera *camera, float y_offset) {
  if (camera->fov >= 1.0f && camera->fov <= 45.0f) {
    camera->fov -= y_offset;
  }

  if (camera->fov <= 1.0f) {
    camera->fov = 1.0f;
  }

  if (camera->fov >= 45.0f) {
    camera->fov = 45.0f;
  }
}
