#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <stdbool.h>

GLFWwindow *window_create(unsigned int width, unsigned int height,
                          const char *title, bool vsync);
void window_destroy(GLFWwindow *window);

#endif /* WINDOW_H */
