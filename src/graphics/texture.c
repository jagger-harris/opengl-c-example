#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdio.h>

texture texture_create(const char *texture_path, unsigned int color_mode) {
  texture texture;
  unsigned char *image_data;

  stbi_set_flip_vertically_on_load(1);
  image_data = stbi_load(texture_path, &texture.width, &texture.height,
                         &texture.nr_channels, 0);

  glGenTextures(1, &texture.texture);
  glBindTexture(GL_TEXTURE_2D, texture.texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  if (image_data) {
    glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)color_mode, (GLint)texture.width,
                 (GLint)texture.height, 0, (GLenum)color_mode, GL_UNSIGNED_BYTE,
                 image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    fprintf(stderr, "ERROR_TEXTURE_FAILED_TO_LOAD_TEXTURE:\n%s\n",
            texture_path);
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(image_data);
  stbi_set_flip_vertically_on_load(0);

  return texture;
}

void texture_use(texture *texture, unsigned int texture_level) {
  glActiveTexture((GLenum)texture_level);
  glBindTexture(GL_TEXTURE_2D, (GLuint)texture->texture);
}
