#ifndef GLDEBUG_H
#define GLDEBUG_H

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

#define MAX_ERROR_BUFFER_SIZE 128
#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line) {
  GLenum error_code;

  while ((error_code = glGetError()) != GL_NO_ERROR) {
    char error[MAX_ERROR_BUFFER_SIZE];

    switch (error_code) {
    case GL_INVALID_ENUM:
      strncpy(error, "INVALID_ENUM", MAX_ERROR_BUFFER_SIZE);
      error[MAX_ERROR_BUFFER_SIZE - 1] = '\0';
      break;
    case GL_INVALID_VALUE:
      strncpy(error, "INVALID_VALUE", MAX_ERROR_BUFFER_SIZE);
      error[MAX_ERROR_BUFFER_SIZE - 1] = '\0';
      break;
    case GL_INVALID_OPERATION:
      strncpy(error, "INVALID_OPERATION", MAX_ERROR_BUFFER_SIZE);
      error[MAX_ERROR_BUFFER_SIZE - 1] = '\0';
      break;
    case GL_OUT_OF_MEMORY:
      strncpy(error, "OUT_OF_MEMORY", MAX_ERROR_BUFFER_SIZE);
      error[MAX_ERROR_BUFFER_SIZE - 1] = '\0';
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      strncpy(error, "INVALID_FRAMEBUFFER_OPERATION", MAX_ERROR_BUFFER_SIZE);
      error[MAX_ERROR_BUFFER_SIZE - 1] = '\0';
      break;
    }

    fprintf(stderr, "%s | %s (%i)\n", error, file, line);
  }

  return error_code;
}

#endif /* GLDEBUG_H */
