#include "window.h"
#include "../graphics/camera.h"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

window window_create(int width, int height, int vsync, const char *title) {
  window window;
  GLFWwindow *glfw_window;

  window.camera = camera_create(0.0f, 0.0f, 5.0f, (float)width, (float)height);
  window.title = title;
  window.width = width;
  window.height = height;
  window.vsync = vsync;
  window.mouse_first = 1;
  window.delta_time = 0.0f;
  window.last_frame = 0.0f;

  if (!glfwInit()) {
    const char *glfw_error;

    glfwGetError(&glfw_error);
    fprintf(stderr, "ERROR_GLFW_FAILED_TO_INITIALIZE_GLFW: %s\n", glfw_error);
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (glfw_window == NULL) {
    const char *glfw_error;

    glfwGetError(&glfw_error);
    fprintf(stderr, "ERROR_GLFW_FAILED_TO_CREATE_WINDOW: %s\n", glfw_error);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(glfw_window);
  glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
  glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSwapInterval(vsync);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  window.glfw_window = glfw_window;

  return window;
}

void window_destroy(window *window) {
  glfwDestroyWindow(window->glfw_window);
  glfwTerminate();
}

void window_process(window *window) {
  float current_frame = (float)glfwGetTime();

  window->delta_time = current_frame - window->last_frame;
  window->last_frame = current_frame;

  glfwSwapBuffers(window->glfw_window);
  glfwPollEvents();
}
