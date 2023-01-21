#include "renderer.h"

#include "stb/stb_image.h"

void renderer_clear(float red, float green, float blue, float alpha) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor((GLfloat)red, (GLfloat)green, (GLfloat)blue, (GLfloat)alpha);
}

void renderer_use_shader(shader *shader) { glUseProgram((GLuint)shader->id); }

void renderer_framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height) {
  glViewport(0, 0, (GLint)width, (GLint)height);
}

void renderer_settings() {
  stbi_set_flip_vertically_on_load(true);
  glEnable(GL_DEPTH_TEST);
}
