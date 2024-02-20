#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include <glad/glad.h>

#define TRIANGLE_VERTEX_COUNT 9
#define TRIANGLE_UV_COUNT 6

static const GLfloat TRIANGLE_VERTICES[] = {
    -0.5f, -0.5f, 0.0f, /* Bottom left */
    0.5f,  -0.5f, 0.0f, /* Bottom right */
    0.0f,  0.5f,  0.0f  /* Top */
};

static const GLfloat TRIANGLE_COLOR[] = {
    1.0f, 0.0f, 0.0f, /* Bottom left */
    0.0f, 1.0f, 0.0f, /* Bottom right */
    0.0f, 0.0f, 1.0f  /* Top */
};

static const GLfloat TRIANGLE_UV[] = {
    0.0f, 0.0f, /* Bottom left */
    1.0f, 0.0f, /* Bottom right */
    0.5f, 1.0f  /* Top */
};

typedef struct triangle {
  GLuint vao;
  GLuint vbo_position;
  GLuint vbo_color;
  GLuint vbo_uv;
  GLfloat vertices[TRIANGLE_VERTEX_COUNT];
  GLfloat color[TRIANGLE_VERTEX_COUNT];
  GLfloat uv[TRIANGLE_UV_COUNT];
  shader *shader;
  texture *texture;
  vec3 scale;
  vec3 rotation_axis;
  vec3 translation;
  float rotation_degrees;
} triangle;

triangle triangle_create(shader *shader, texture *texture, float pos_x,
                         float pos_y, float pos_z, float rotation);
void triangle_destroy(triangle *triangle);
void triangle_draw(triangle *triangle, camera *camera);
void triangle_scale(triangle *triangle, float x, float y, float z);
void triangle_rotate(triangle *triangle, vec3 *rotation_axis, float degrees);
void triangle_translate(triangle *triangle, float x, float y, float z);

#endif /* TRIANGLE_H */
