#ifndef QUAD_H
#define QUAD_H

typedef struct quad {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
} quad;

quad quad_create(void);
void quad_destroy(quad quad);
void quad_draw(quad quad);

#endif /* QUAD_H */
