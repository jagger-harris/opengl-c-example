#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

out vec3 color_out;
out vec2 uv_out;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0f);
  uv_out = uv;
  color_out = color;
}
