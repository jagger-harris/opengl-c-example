#ifndef CUBE_H
#define CUBE_H

#include "camera.h"
#include "shader.h"
#include "texture.h"
#include <glad/glad.h>

#define CUBE_VERTEX_COUNT 72
#define CUBE_INDEX_COUNT 36
#define CUBE_UV_COUNT 48

static const GLfloat CUBE_VERTICES[] = {
    /* Front face */
    -0.5f, -0.5f, 0.5f, /* 0: Bottom left */
    0.5f, -0.5f, 0.5f,  /* 1: Bottom right */
    0.5f, 0.5f, 0.5f,   /* 2: Top right*/
    -0.5f, 0.5f, 0.5f,  /* 3: Top left */
    /* Back face */
    0.5f, -0.5f, -0.5f,  /* 4: Bottom right */
    -0.5f, -0.5f, -0.5f, /* 5: Bottom left */
    -0.5f, 0.5f, -0.5f,  /* 6: Top left */
    0.5f, 0.5f, -0.5f,   /* 7: Top right */
    /* Right face */
    0.5f, -0.5f, 0.5f,  /* 8: Bottom right */
    0.5f, -0.5f, -0.5f, /* 9: Bottom left */
    0.5f, 0.5f, -0.5f,  /* 10: Top left */
    0.5f, 0.5f, 0.5f,   /* 11: Top right */
    /* Left face */
    -0.5f, -0.5f, -0.5f, /* 12: Bottom left */
    -0.5f, -0.5f, 0.5f,  /* 13: Bottom right */
    -0.5f, 0.5f, 0.5f,   /* 14: Top right */
    -0.5f, 0.5f, -0.5f,  /* 15: Top left */
    /* Top face */
    0.5f, 0.5f, -0.5f,  /* 16: Bottom right */
    -0.5f, 0.5f, -0.5f, /* 17: Bottom left */
    -0.5f, 0.5f, 0.5f,  /* 18: Top left */
    0.5f, 0.5f, 0.5f,   /* 19: Top right */
    /* Bottom face */
    -0.5f, -0.5f, -0.5f, /* 20: Bottom left */
    0.5f, -0.5f, -0.5f,  /* 21: Bottom right */
    0.5f, -0.5f, 0.5f,   /* 22: Top right */
    -0.5f, -0.5f, 0.5f   /* 23: Top left */
};

static const GLuint CUBE_INDICES[] = {
    0,  1,  2,  0,  2,  3,  /* Front face */
    4,  5,  6,  4,  6,  7,  /* Back face */
    8,  9,  10, 8,  10, 11, /* Right face */
    12, 13, 14, 12, 14, 15, /* Left face */
    16, 17, 18, 16, 18, 19, /* Top face */
    20, 21, 22, 20, 22, 23  /* Bottom face*/
};

static const GLfloat CUBE_UV[] = {
    /* Front face */
    0.0f, 0.0f, /* Bottom left */
    1.0f, 0.0f, /* Bottom right */
    1.0f, 1.0f, /* Top right */
    0.0f, 1.0f, /* Top left */
    /* Back face */
    0.0f, 0.0f, /* Bottom right */
    1.0f, 0.0f, /* Bottom left */
    1.0f, 1.0f, /* Top left */
    0.0f, 1.0f, /* Top right */
    /* Right face */
    0.0f, 0.0f, /* Bottom left */
    1.0f, 0.0f, /* Bottom right */
    1.0f, 1.0f, /* Top right */
    0.0f, 1.0f, /* Top left */
    /* Left face */
    0.0f, 0.0f, /* Bottom right */
    1.0f, 0.0f, /* Bottom left */
    1.0f, 1.0f, /* Top left */
    0.0f, 1.0f, /* Top right */
    /* Top face */
    0.0f, 0.0f, /* Bottom left */
    1.0f, 0.0f, /* Bottom right */
    1.0f, 1.0f, /* Top right */
    0.0f, 1.0f, /* Top left */
    /* Bottom face */
    0.0f, 0.0f, /* Bottom right */
    1.0f, 0.0f, /* Bottom left */
    1.0f, 1.0f, /* Top left */
    0.0f, 1.0f  /* Top right */
};

typedef struct cube {
  GLuint vao;
  GLuint ebo;
  GLuint vbo_position;
  GLuint vbo_uv;
  GLfloat vertices[CUBE_VERTEX_COUNT];
  GLuint indices[CUBE_INDEX_COUNT];
  GLfloat uv[CUBE_UV_COUNT];
  shader *shader;
  texture *texture;
  vec3 scale;
  vec3 rotation_axis;
  vec3 translation;
  float rotation_degrees;
} cube;

cube cube_create(shader *shader, texture *texture, float pos_x, float pos_y,
                 float pos_z, float rotation);
void cube_destroy(cube *cube);
void cube_draw(cube *cube, camera *camera);
void cube_scale(cube *cube, float x, float y, float z);
void cube_rotate(cube *cube, vec3 *rotation_axis, float degrees);
void cube_translate(cube *cube, float x, float y, float z);

#endif /* CUBE_H */
