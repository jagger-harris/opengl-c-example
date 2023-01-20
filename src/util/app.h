#ifndef APP_H
#define APP_H

#include "GLFW/glfw3.h"
#include "camera.h"

#include <stdbool.h>

typedef struct {
  GLFWwindow *window;
  camera *camera;
  unsigned int height;
  unsigned int width;
  const char *title;
  bool vsync;
  float last_frame;
  float delta_time;
} app;

app app_create(camera *camera, unsigned int width, unsigned int height,
               const char *title, bool vsync);

void app_destroy(app *app);

void app_run(app *app);

#endif /* APP_H */
