#ifndef QUAD_H
#define QUAD_H

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include <glad/glad.h>

#define QUAD_VERTEX_COUNT 12
#define QUAD_INDEX_COUNT 6
#define QUAD_UV_COUNT 8

static const GLfloat QUAD_VERTICES[] = {
    -0.5f, -0.5f, 0.0f, /* 0: Bottom left */
    0.5f,  -0.5f, 0.0f, /* 1: Bottom right */
    0.5f,  0.5f,  0.0f, /* 2: Top right*/
    -0.5f, 0.5f,  0.0f, /* 3: Top left */
};

static const GLuint QUAD_INDICES[] = {
    0, 1, 2, /* Right quad*/
    0, 2, 3  /* Left quad*/
};

static const GLfloat QUAD_COLOR[] = {
    1.0f, 0.0f, 0.0f, /* Bottom left */
    0.0f, 1.0f, 0.0f, /* Bottom right */
    0.0f, 0.0f, 1.0f, /* Top right*/
    1.0f, 1.0f, 0.0f  /* Top left*/
};

static const GLfloat QUAD_UV[] = {
    0.0f, 0.0f, /* Bottom left */
    1.0f, 0.0f, /* Bottom right */
    1.0f, 1.0f, /* Top right*/
    0.0f, 1.0f  /* Top left*/
};

typedef struct quad {
  GLuint vao;
  GLuint ebo;
  GLuint vbo_position;
  GLuint vbo_color;
  GLuint vbo_uv;
  GLfloat vertices[QUAD_VERTEX_COUNT];
  GLuint indices[QUAD_INDEX_COUNT];
  GLfloat color[QUAD_VERTEX_COUNT];
  GLfloat uv[QUAD_UV_COUNT];
  shader *shader;
  texture *texture;
  vec3 scale;
  vec3 rotation_axis;
  vec3 translation;
  float rotation_degrees;
} quad;

quad quad_create(shader *shader, texture *texture, float pos_x, float pos_y,
                 float pos_z, float rotation);
void quad_destroy(quad *quad);
void quad_draw(quad *quad, camera *camera);
void quad_scale(quad *quad, float x, float y, float z);
void quad_rotate(quad *quad, vec3 *rotation_axis, float degrees);
void quad_translate(quad *quad, float x, float y, float z);

#endif /* QUAD_H */
