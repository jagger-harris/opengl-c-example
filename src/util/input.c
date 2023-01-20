#include "input.h"
#include "math/math.h"

#include <math.h>
#include <stdbool.h>

void input_handle_keys(app *app);
void input_handle_mouse(app *app);

void input_handle(app *app) {
  input_handle_keys(app);
  input_handle_mouse(app);
}

void input_handle_keys(app *app) {
  GLFWwindow *window = app->window;
  camera *camera = app->camera;
  float velocity = camera->speed * app->delta_time;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera_keyboard_input(camera, FORWARD, velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera_keyboard_input(camera, BACKWARD, velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera_keyboard_input(camera, LEFT, velocity);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera_keyboard_input(camera, RIGHT, velocity);
  }
}

void input_handle_mouse(app *app) {
  camera *camera = app->camera;
  double pos_x;
  double pos_y;
  float offset_x;
  float offset_y;

  glfwGetCursorPos(app->window, &pos_x, &pos_y);

  offset_x = (float)pos_x - camera->last_x;
  offset_y = camera->last_y - (float)pos_y;

  camera->last_x = (float)pos_x;
  camera->last_y = (float)pos_y;

  camera_mouse_input(camera, offset_x, offset_y);
}
