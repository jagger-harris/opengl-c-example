#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "quad.h"
#include "triangle.h"
#include "../util/window.h"

typedef enum shaders {
  CUBE_SHADER,
  QUAD_SHADER,
  TRIANGLE_SHADER,
  NUM_OF_SHADERS
} shaders;

typedef enum textures {
  CONTAINER_TEXTURE,
  NUM_OF_TEXTURES
} textures;

typedef enum cubes {
  CUBE,
  NUM_OF_CUBES
} cubes;

typedef enum quads {
  QUAD,
  NUM_OF_QUADS
} quads;

typedef enum triangles {
  TRIANGLE,
  NUM_OF_TRIANGLES
} triangles;

typedef struct renderer {
  shader shaders[NUM_OF_SHADERS];
  texture textures[NUM_OF_TEXTURES];
  cube cubes[NUM_OF_CUBES];
  quad quads[NUM_OF_QUADS];
  triangle triangles[NUM_OF_TRIANGLES];
} renderer;

renderer renderer_create(void);
void renderer_clear(renderer *renderer);
void renderer_swap(renderer *renderer);
void renderer_draw(renderer *renderer, window *window);

#endif /* RENDERER_H */
