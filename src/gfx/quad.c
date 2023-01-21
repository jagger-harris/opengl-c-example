#include "quad.h"

#include "glad/gl.h"

quad quad_create() {
  quad quad;
  
  /* Quad vertices */
  static const float vertices[] = {
    // Positions(x, y, z)   // Colors           // Texture coords
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 0.0f,   1.0f, 0.0f
  };

  /* Quad indices */
  static const unsigned int indices[] = {
    0, 1, 2, // First triangle
    0, 2, 3  // Second triangle
  };

  /* Generate array/buffer objects */
  glGenVertexArrays(1, &quad.vao);
  glGenBuffers(1, &quad.vbo);
  glGenBuffers(1, &quad.ebo);

  /* Bind array/buffer objects with corresponding data*/
  glBindVertexArray((GLuint)quad.vao);
  glBindBuffer(GL_ARRAY_BUFFER, (GLuint)quad.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)quad.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  /* Position */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  /* Color */
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  /* Texture */
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  /* Unbind vertex/buffer arrays/objects */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return quad;
}

void quad_destroy(quad quad) {
  glDeleteVertexArrays(1, &quad.vao);
  glDeleteBuffers(1, &quad.vbo);
  glDeleteBuffers(1, &quad.ebo);
}

void quad_draw(quad quad) {
  glBindVertexArray((GLuint)quad.vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
