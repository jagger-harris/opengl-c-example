#ifndef CUBE_H
#define CUBE_H

typedef struct cube {
  unsigned int vao;
  unsigned int vbo;
} cube;

static const float vertices[] = {
  // Positions(x, y, z)     // Texture coords
  
  /* Quad front */
  -0.5f, -0.5f, 0.5f,       0.0f, 0.0f,
  -0.5f, 0.5f, 0.5f,        0.0f, 1.0f,
  0.5f, 0.5f, 0.5f,         1.0f, 1.0f,
  -0.5f, -0.5f, 0.5f,       0.0f, 0.0f,
  0.5f, 0.5f, 0.5f,         1.0f, 1.0f,
  0.5f, -0.5f, 0.5f,        1.0f, 0.0f,

  /* Quad left */
  -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,       0.0f, 1.0f,
  -0.5f, 0.5f, 0.5f,        1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
  -0.5f, 0.5f, 0.5f,        1.0f, 1.0f,
  -0.5f, -0.5f, 0.5f,       1.0f, 0.0f,

  /* Quad back */
  0.5f, -0.5f, -0.5f,       0.0f, 0.0f,
  0.5f, 0.5f, -0.5f,        0.0f, 1.0f,
  -0.5f, 0.5f, -0.5f,       1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,       0.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,       1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,      1.0f, 0.0f,

  /* Quad right */
  0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
  0.5f, 0.5f, 0.5f,         0.0f, 1.0f,
  0.5f, 0.5f, -0.5f,        1.0f, 1.0f,
  0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
  0.5f, 0.5f, -0.5f,        1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,       1.0f, 0.0f,

  /* Quad top */
  -0.5f, 0.5f, 0.5f,        0.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,       0.0f, 1.0f,
  0.5f, 0.5f, -0.5f,        1.0f, 1.0f,
  -0.5f, 0.5f, 0.5f,        0.0f, 0.0f,
  0.5f, 0.5f, -0.5f,        1.0f, 1.0f,
  0.5f, 0.5f, 0.5f,         1.0f, 0.0f,

  /* Quad bottom */
  -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
  -0.5f, -0.5f, 0.5f,       0.0f, 1.0f,
  0.5f, -0.5f, 0.5f,        1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
  0.5f, -0.5f, 0.5f,        1.0f, 1.0f,
  0.5f, -0.5f, -0.5f,       1.0f, 0.0f
};

cube cube_create();
void cube_destroy(cube cube);
void cube_draw(cube cube);

#endif /* CUBE_H */
