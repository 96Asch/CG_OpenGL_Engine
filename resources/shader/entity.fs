#version 430 core

in vec2 tex_coords;

uniform sampler2D texture;

out vec4 out_color;

void main() {
  out_color = texture2D(texture, tex_coords);
}
