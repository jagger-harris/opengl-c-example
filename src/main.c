#include "util/app.h"
#include "util/camera.h"

#include <stdbool.h>
#include <stdio.h>

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "OpenGL Window"
#define APP_VSYNC true

int main() {
  camera *camera = camera_create(0.0f, 0.0f, 3.0f, -90.0f, 0.0f, 2.5f, 0.1f,
                                 APP_WIDTH, APP_HEIGHT);
  app app = app_create(camera, APP_WIDTH, APP_HEIGHT, APP_TITLE, APP_VSYNC);

  app_run(&app);
  app_destroy(&app);
}
