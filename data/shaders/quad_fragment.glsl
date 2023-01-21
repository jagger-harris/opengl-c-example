#version 330 core

in vec3 color_out;
in vec2 texture_coords_out;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float opacity;

void main() {
  color = mix(texture(texture1, texture_coords_out), texture(texture2, texture_coords_out), 0.2) * vec4(color_out, 1.0f);
}
