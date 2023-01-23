#include "util/app.h"
#include "util/camera.h"

#include <stdbool.h>
#include <stdio.h>

#define APP_WIDTH 1280
#define APP_HEIGHT 720
#define APP_TITLE "OpenGL Window"
#define APP_VSYNC true

int main() {
  app app = app_create(APP_WIDTH, APP_HEIGHT, APP_TITLE, APP_VSYNC);

  app_run(&app);
  app_destroy(&app);

  return 0;
}
