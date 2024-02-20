#version 330 core

in vec2 uv_out;

out vec4 color;

uniform float alpha;
uniform sampler2D texture_sampler;

void main() {
  color = texture(texture_sampler, uv_out);
}
