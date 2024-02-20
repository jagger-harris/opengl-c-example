#include "quad.h"
#include "gldebug.h"

quad quad_create(shader *shader, texture *texture, float pos_x, float pos_y,
                 float pos_z, float rotation) {
  quad quad;
  int i;

  for (i = 0; i < QUAD_VERTEX_COUNT; i++) {
    quad.vertices[i] = QUAD_VERTICES[i];
  }

  for (i = 0; i < QUAD_INDEX_COUNT; i++) {
    quad.indices[i] = QUAD_INDICES[i];
  }

  for (i = 0; i < QUAD_VERTEX_COUNT; i++) {
    quad.color[i] = QUAD_COLOR[i];
  }

  for (i = 0; i < QUAD_UV_COUNT; i++) {
    quad.uv[i] = QUAD_UV[i];
  }

  quad.shader = shader;
  quad.texture = texture;
  quad.scale = vec3_create_same_value(1.0f);
  quad.rotation_axis = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  quad.rotation_degrees = 0.0f;
  quad.translation = vec3_create_from_values(pos_x, pos_y, pos_z);

  glGenVertexArrays(1, &quad.vao);
  glBindVertexArray(quad.vao);

  glGenBuffers(1, &quad.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad.indices), quad.indices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &quad.vbo_position);
  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_position);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad.vertices), quad.vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &quad.vbo_color);
  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad.color), quad.color, GL_STATIC_DRAW);

  glGenBuffers(1, &quad.vbo_uv);
  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_uv);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad.uv), quad.uv, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_position);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_color);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo_uv);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(2);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return quad;
}

void quad_destroy(quad *quad) {
  glDeleteVertexArrays(1, &quad->vao);
  glDeleteBuffers(1, &quad->ebo);
  glDeleteBuffers(1, &quad->vbo_position);
  glDeleteBuffers(1, &quad->vbo_color);
  glDeleteBuffers(1, &quad->vbo_uv);
}

void quad_draw(quad *quad, camera *camera) {
  mat4 model = mat4_create_identity();
  mat4 mvp = mat4_create_identity();

  model = mat4_scale(&model, &quad->scale);
  model = mat4_rotate(&model, &quad->rotation_axis, quad->rotation_degrees);
  model = mat4_translate(&model, &quad->translation);
  mvp = mat4_multiply(&mvp, &camera->projection);
  mvp = mat4_multiply(&mvp, &camera->view);
  mvp = mat4_multiply(&mvp, &model);

  texture_use(quad->texture, GL_TEXTURE0);
  shader_use(quad->shader);
  shader_set_mat4(quad->shader, "mvp", &mvp);

  glBindVertexArray(quad->vao);
  glDrawElements(GL_TRIANGLES, QUAD_INDEX_COUNT, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void quad_scale(quad *quad, float x, float y, float z) {
  quad->scale.x = x;
  quad->scale.y = y;
  quad->scale.z = z;
}

void quad_translate(quad *quad, float x, float y, float z) {
  quad->translation.x = x;
  quad->translation.y = y;
  quad->translation.z = z;
}

void quad_rotate(quad *quad, vec3 *rotation_axis, float degrees) {
  quad->rotation_axis = *rotation_axis;
  quad->rotation_degrees = degrees;
}
