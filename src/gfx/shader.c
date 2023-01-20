#include "shader.h"

#include "glad/gl.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_SHADER_BYTES 10000
#define MAX_ERROR_LOG_BYTES 512

shader shader_create(const char *vertex_shader_file_path,
                     const char *fragment_shader_file_path) {
  shader shader;
  GLuint vertex_shader;
  GLuint fragment_shader;
  const char *vertex_shader_code = shader_read_file(vertex_shader_file_path);
  const char *fragment_shader_code =
      shader_read_file(fragment_shader_file_path);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
  glCompileShader(vertex_shader);
  shader_check_errors(vertex_shader, GL_VERTEX_SHADER);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
  glCompileShader(fragment_shader);
  shader_check_errors(fragment_shader, GL_FRAGMENT_SHADER);

  shader.id = glCreateProgram();
  glAttachShader(shader.id, vertex_shader);
  glAttachShader(shader.id, fragment_shader);
  glLinkProgram(shader.id);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  free((void *)vertex_shader_code);
  free((void *)fragment_shader_code);

  return shader;
}

char *shader_read_file(const char *file_path) {
  FILE *fp = fopen(file_path, "r");
  char *code = malloc(MAX_SHADER_BYTES);

  if (fp == NULL) {
    fprintf(stderr, "ERROR_SHADER_FILE_COULD_NOT_OPEN_SHADER_FILE:\n%s\n",
            file_path);

    return NULL;
  }

  fread(code, 1, MAX_SHADER_BYTES, fp);
  fclose(fp);

  return code;
}

void shader_check_errors(unsigned int shader, unsigned int type) {
  GLint success;
  char info_log[MAX_ERROR_LOG_BYTES];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, MAX_ERROR_LOG_BYTES, NULL, info_log);
    fprintf(stderr, "ERROR_SHADER_FAILED_TO_COMPILE_SHADER_");

    if (type == GL_VERTEX_SHADER) {
      fprintf(stderr, "VERTEX");
    } else {
      fprintf(stderr, "FRAGMENT");
    }

    fprintf(stderr, ":\n%s\n", info_log);
  }
}

void shader_set_bool(shader shader, const char *name, bool value) {
  glUniform1i(glGetUniformLocation(shader.id, name), (GLint)value);
}

void shader_set_int(shader shader, const char *name, int value) {
  glUniform1i(glGetUniformLocation(shader.id, name), (GLint)value);
}

void shader_set_float(shader shader, const char *name, float value) {
  glUniform1f(glGetUniformLocation(shader.id, name), (GLfloat)value);
}

void shader_set_mat4(shader shader, const char *name, mat4 *value) {
  glUniformMatrix4fv(glGetUniformLocation(shader.id, name), 1, GL_FALSE,
                     (const GLfloat *)value);
}
