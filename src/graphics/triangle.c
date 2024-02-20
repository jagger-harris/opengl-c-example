#include "triangle.h"

triangle triangle_create(shader *shader, texture *texture, float pos_x,
                         float pos_y, float pos_z, float rotation) {
  triangle triangle;
  int i;

  for (i = 0; i < TRIANGLE_VERTEX_COUNT; i++) {
    triangle.vertices[i] = TRIANGLE_VERTICES[i];
  }

  for (i = 0; i < TRIANGLE_VERTEX_COUNT; i++) {
    triangle.color[i] = TRIANGLE_COLOR[i];
  }

  for (i = 0; i < TRIANGLE_UV_COUNT; i++) {
    triangle.uv[i] = TRIANGLE_UV[i];
  }

  triangle.shader = shader;
  triangle.texture = texture;
  triangle.scale = vec3_create_same_value(1.0f);
  triangle.rotation_axis = vec3_create_from_values(0.0f, 1.0f, 0.0f);
  triangle.rotation_degrees = 0.0f;
  triangle.translation = vec3_create_from_values(pos_x, pos_y, pos_z);

  glGenVertexArrays(1, &triangle.vao);
  glBindVertexArray(triangle.vao);

  glGenBuffers(1, &triangle.vbo_position);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_position);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.vertices), triangle.vertices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &triangle.vbo_color);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_color);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.color), triangle.color,
               GL_STATIC_DRAW);

  glGenBuffers(1, &triangle.vbo_uv);
  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_uv);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.uv), triangle.uv,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_position);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_color);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo_uv);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(2);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return triangle;
}

void triangle_destroy(triangle *triangle) {
  glDeleteVertexArrays(1, &triangle->vao);
  glDeleteBuffers(1, &triangle->vbo_position);
  glDeleteBuffers(1, &triangle->vbo_color);
  glDeleteBuffers(1, &triangle->vbo_uv);
}

void triangle_draw(triangle *triangle, camera *camera) {
  mat4 model = mat4_create_identity();
  mat4 mvp = mat4_create_identity();

  model = mat4_scale(&model, &triangle->scale);
  model =
      mat4_rotate(&model, &triangle->rotation_axis, triangle->rotation_degrees);
  model = mat4_translate(&model, &triangle->translation);
  mvp = mat4_multiply(&mvp, &camera->projection);
  mvp = mat4_multiply(&mvp, &camera->view);
  mvp = mat4_multiply(&mvp, &model);

  texture_use(triangle->texture, GL_TEXTURE0);
  shader_use(triangle->shader);
  shader_set_mat4(triangle->shader, "mvp", &mvp);

  glBindVertexArray(triangle->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void triangle_scale(triangle *triangle, float x, float y, float z) {
  triangle->scale.x = x;
  triangle->scale.y = y;
  triangle->scale.z = z;
}

void triangle_translate(triangle *triangle, float x, float y, float z) {
  triangle->translation.x = x;
  triangle->translation.y = y;
  triangle->translation.z = z;
}

void triangle_rotate(triangle *triangle, vec3 *rotation_axis, float degrees) {
  triangle->rotation_axis = *rotation_axis;
  triangle->rotation_degrees = degrees;
}
