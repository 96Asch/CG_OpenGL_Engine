#version 430 core

const int MAX_POINT_LIGHTS = 5;

layout (location=0) in vec3 position;
layout (location=1) in vec2 uv;
layout (location=2) in vec3 normal;

out TD_DATA {
	out vec2 tex0;
	out vec3 normal0;
	out vec3 world0;
} outData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(position, 1.0);
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 Normal = normalMatrix * normal;
	outData.tex0 = uv;
	outData.normal0 =Normal;
	outData.world0 = (model * vec4(position, 1.0)).xyz;
}
