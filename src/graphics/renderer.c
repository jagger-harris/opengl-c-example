#include "renderer.h"
#include "../math/math.h"
#include "GLFW/glfw3.h"
#include "camera.h"
#include "quad.h"
#include "triangle.h"
#include <math.h>

renderer renderer_create(void) {
  renderer renderer;

  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  renderer.shaders[CUBE_SHADER] = shader_create(
      "data/shaders/cube_vertex.glsl", "data/shaders/cube_fragment.glsl");
  renderer.shaders[QUAD_SHADER] = shader_create(
      "data/shaders/quad_vertex.glsl", "data/shaders/quad_fragment.glsl");
  renderer.shaders[TRIANGLE_SHADER] =
      shader_create("data/shaders/triangle_vertex.glsl",
                    "data/shaders/triangle_fragment.glsl");

  renderer.textures[CONTAINER_TEXTURE] =
      texture_create("data/assets/images/container.jpg", GL_RGB);

  renderer.cubes[CUBE] = cube_create(&renderer.shaders[CUBE_SHADER],
                                     &renderer.textures[CONTAINER_TEXTURE],
                                     0.0f, 0.0f, 0.0f, 90.0f);
  renderer.quads[QUAD] = quad_create(&renderer.shaders[QUAD_SHADER],
                                     &renderer.textures[CONTAINER_TEXTURE],
                                     0.0f, 0.0f, 1.0f, 90.0f);
  renderer.triangles[TRIANGLE] = triangle_create(
      &renderer.shaders[TRIANGLE_SHADER], &renderer.textures[CONTAINER_TEXTURE],
      0.0f, 0.0f, 2.0f, 90.0f);

  return renderer;
}

void renderer_clear(renderer *renderer) {
  glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_draw(renderer *renderer, window *window) {
  cube *cube = &renderer->cubes[CUBE];

  camera_update_projection(&window->camera);
  cube_draw(cube, &window->camera);
}
