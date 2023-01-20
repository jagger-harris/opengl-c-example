#ifndef RENDERER_H
#define RENDERER_H

#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "shader.h"

void renderer_clear(float red, float green, float blue, float alpha);
void renderer_use_shader(shader shader);
void renderer_framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
void renderer_settings();

#endif /* RENDERER_H */
