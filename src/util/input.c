#include "input.h"

void input_handle_keys(window *window) {
  camera *camera = &window->camera;
  GLFWwindow *glfw_window = window->glfw_window;

  if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(glfw_window, 1);
  }

  camera_process_key_input(camera, glfw_window, window->delta_time);
}

void input_handle_mouse(window *window) {
  camera *camera = &window->camera;
  GLFWwindow *glfw_window = window->glfw_window;
  double pos_x;
  double pos_y;
  float offset_x;
  float offset_y;

  glfwGetCursorPos(glfw_window, &pos_x, &pos_y);

  if (window->mouse_first) {
    window->mouse_last_x = pos_x;
    window->mouse_last_y = pos_y;
    window->mouse_first = 0;
  }

  offset_x = (float)pos_x - window->mouse_last_x;
  offset_y = window->mouse_last_y - (float)pos_y;

  window->mouse_last_x = (float)pos_x;
  window->mouse_last_y = (float)pos_y;

  camera_process_mouse_movement(camera, offset_x, offset_y);
}

void input_handle(window *window) {
  input_handle_keys(window);
  input_handle_mouse(window);
}
