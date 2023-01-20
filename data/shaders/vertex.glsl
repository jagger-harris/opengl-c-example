#version 330 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
layout (location = 1) in vec2 texture_coords;

//out vec3 color_out;
out vec2 texture_coords_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  //color_out = color;
  texture_coords_out = texture_coords;
}
