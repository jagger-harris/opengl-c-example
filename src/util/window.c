#include "window.h"
#include "gfx/renderer.h"

#include <stdio.h>

GLFWwindow *window_create(unsigned int width, unsigned int height,
                          const char *title, bool vsync) {
  GLFWwindow *window = NULL;

  if (!glfwInit()) {
    fprintf(stderr, "ERROR_GLFW_FAILED_TO_INITIALIZE\n");

    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  if (window == NULL) {
    fprintf(stderr, "ERROR_GLFW_FAILED_TO_CREATE_WINDOW\n");

    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, renderer_framebuffer_size_callback);

  /* Set input mode */
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  /* Check if GLAD is not initalized */
  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "ERROR_GLAD_FAILED_TO_INITIALIZE\n");

    return NULL;
  }

  /* Enable vsync*/
  if (vsync) {
    glfwSwapInterval(1);
  }

  return window;
}

void window_destroy(GLFWwindow *window) {
  glfwTerminate();

  if (window) {
    glfwDestroyWindow(window);
  }
}
