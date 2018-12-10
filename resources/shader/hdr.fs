#version 430 core

out vec4 fragColor;

in vec2 tex0;

uniform sampler2D colorTex;
uniform sampler2D brightTex;
uniform float exposure;

vec4 calcHdr(vec2 texC) {
  const float gamma = 2.2;
  vec3 hdrColor = texture(brightTex, texC).rgb;
  vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
  return vec4(result = pow(result, vec3(1.0 / gamma)), 1);
}

void main() {
  vec4 color = texture2D(colorTex, tex0);
  vec4 bright = calcHdr(tex0);
  fragColor = color + (bright * 2);
}
