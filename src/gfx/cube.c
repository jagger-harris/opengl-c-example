#include "cube.h"

#include "glad/gl.h"

cube cube_create(void) {
  cube cube;

  /* Generate array/buffer objects */
  glGenVertexArrays(1, &cube.vao);
  glGenBuffers(1, &cube.vbo);

  /* Bind array/buffer objects with corresponding data*/
  glBindVertexArray((GLuint)cube.vao);
  glBindBuffer(GL_ARRAY_BUFFER, (GLuint)cube.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  /* Position */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  /* Texture */
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  /* Unbind vertex/buffer arrays/objects */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return cube;
}

void cube_destroy(cube cube) {
  glDeleteVertexArrays(1, &cube.vao);
  glDeleteBuffers(1, &cube.vbo);
}

void cube_draw(cube cube) {
  glBindVertexArray((GLuint)cube.vao);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}