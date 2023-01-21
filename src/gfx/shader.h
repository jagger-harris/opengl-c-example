#ifndef SHADER_H
#define SHADER_H

#include "math/mat4.h"

#include <stdbool.h>

typedef struct shader {
  unsigned int id;
} shader;

shader shader_create(const char *vertex_shader_file_path,
                     const char *fragment_shader_file_path);
char *shader_read_file(const char *file_path);
void shader_check_errors(unsigned int *shader, unsigned int type);
void shader_set_bool(shader *shader, const char *name, bool value);
void shader_set_int(shader *shader, const char *name, int value);
void shader_set_float(shader *shader, const char *name, float value);
void shader_set_mat4(shader *shader, const char *name, mat4 *value);

#endif /* SHADER_H */
