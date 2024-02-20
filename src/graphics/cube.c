#include "cube.h"

cube cube_create(shader *shader, texture *texture, float pos_x, float pos_y,
                 float pos_z, float rotation) {
  cube cube;
  int i;

  for (i = 0; i < CUBE_VERTEX_COUNT; i++) {
    cube.vertices[i] = CUBE_VERTICES[i];
  }

  for (i = 0; i < CUBE_INDEX_COUNT; i++) {
    cube.indices[i] = CUBE_INDICES[i];
  }

  for (i = 0; i < CUBE_UV_COUNT; i++) {
    cube.uv[i] = CUBE_UV[i];
  }

  cube.shader = shader;
  cube.texture = texture;
  cube.scale = vec3_create_same_value(1.0f);
  cube.rotation_axis = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  cube.rotation_degrees = 0.0f;
  cube.translation = vec3_create_from_values(pos_x, pos_y, pos_z);

  glGenVertexArrays(1, &cube.vao);
  glBindVertexArray(cube.vao);

  glGenBuffers(1, &cube.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indices), cube.indices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &cube.vbo_position);
  glBindBuffer(GL_ARRAY_BUFFER, cube.vbo_position);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &cube.vbo_uv);
  glBindBuffer(GL_ARRAY_BUFFER, cube.vbo_uv);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube.uv), cube.uv, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, cube.vbo_position);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, cube.vbo_uv);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(1);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return cube;
}

void cube_destroy(cube *cube) {
  glDeleteVertexArrays(1, &cube->vao);
  glDeleteBuffers(1, &cube->ebo);
  glDeleteBuffers(1, &cube->vbo_position);
  glDeleteBuffers(1, &cube->vbo_uv);
}

void cube_draw(cube *cube, camera *camera) {
  mat4 model = mat4_create_identity();
  mat4 mvp = mat4_create_identity();

  model = mat4_scale(&model, &cube->scale);
  model = mat4_rotate(&model, &cube->rotation_axis, cube->rotation_degrees);
  model = mat4_translate(&model, &cube->translation);
  mvp = mat4_multiply(&mvp, &camera->projection);
  mvp = mat4_multiply(&mvp, &camera->view);
  mvp = mat4_multiply(&mvp, &model);

  texture_use(cube->texture, GL_TEXTURE0);
  shader_use(cube->shader);
  shader_set_mat4(cube->shader, "mvp", &mvp);

  glBindVertexArray(cube->vao);
  glDrawElements(GL_TRIANGLES, CUBE_INDEX_COUNT, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void cube_scale(cube *cube, float x, float y, float z) {
  cube->scale.x = x;
  cube->scale.y = y;
  cube->scale.z = z;
}

void cube_translate(cube *cube, float x, float y, float z) {
  cube->translation.x = x;
  cube->translation.y = y;
  cube->translation.z = z;
}

void cube_rotate(cube *cube, vec3 *rotation_axis, float degrees) {
  cube->rotation_axis = *rotation_axis;
  cube->rotation_degrees = degrees;
}
