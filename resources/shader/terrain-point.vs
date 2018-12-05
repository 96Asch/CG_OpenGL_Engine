#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec2 uv;
layout (location=2) in vec3 vertexNormal;

out vec2 outTexCoord;
out vec3 mvVertexNormal;
out vec3 mvVertexPos;
out vec3 toLightVector;

uniform struct PointLight {
    vec3 color;
    vec3 position;
    float intensity;
    vec3 attenuation;
} pointLight;

uniform mat4 mvp;
uniform mat4 mv;

void main() {
  vec4 mvPos = mv * vec4(position,1.0);
  gl_Position = mvp * vec4(position, 1.0);

  outTexCoord = uv;

	toLightVector = pointLight.position - mvPos.xyz;

 	mvVertexPos = -mvPos.xyz;
  mvVertexNormal = normalize(mv * vec4(vertexNormal, 0.0)).xyz;
}
