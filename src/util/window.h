#ifndef WINDOW_H
#define WINDOW_H

#include "../graphics/camera.h"
#include <GLFW/glfw3.h>

typedef struct window {
  GLFWwindow *glfw_window;
  camera camera;
  const char *title;
  int width;
  int height;
  int vsync;
  int error;
  int mouse_first;
  float delta_time;
  float last_frame;
  float mouse_last_x;
  float mouse_last_y;
} window;

window window_create(int width, int height, int vsync, const char *title);
void window_destroy(window *window);
void window_process(window *window);

#endif /* WINDOW_H */
