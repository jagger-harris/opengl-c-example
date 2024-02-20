#include "util/input.h"
#include "graphics/renderer.h"
#include "util/window.h"
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_VSYNC 1
#define WINDOW_TITLE "OpenGL Window"

int main(int argc, char **argv) {
  window window = window_create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_VSYNC, WINDOW_TITLE);
  renderer renderer = renderer_create();

  while (!glfwWindowShouldClose(window.glfw_window)) {
    renderer_clear(&renderer);
    renderer_draw(&renderer, &window);
    window_process(&window);
    input_handle(&window);
  }

  return 0;
}
