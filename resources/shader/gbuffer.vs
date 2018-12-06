#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out TD_DATA {
  vec2 tex0;
  vec3 normal0;
  vec3 world0;
} outData;


uniform mat4 model;
uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  vec4 worldPos = model * vec4(position, 1.0);
  outData.world0 = worldPos.xyz;
  outData.tex0 = uv;
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  outData.normal0 = normalMatrix * normal;
}
