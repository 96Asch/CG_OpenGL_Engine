#version 430 core

const int MAX_POINT_LIGHTS = 5;

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 vertexNormal;

out vec2 tex0;
out vec3 normal0;
out vec3 world0;
out float vis0;

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform mat4 model;
uniform mat4 mvp;

float calcFog(Fog f, vec4 positionRelativeToCam) {
	float vis = 0;
	float distance = length(positionRelativeToCam.xyz);
	vis = exp(-pow((distance* f.density), f.gradient));
	vis = clamp(vis,0.0,1.0);
	return vis;
}

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    vec4 mvPos = model * vec4(position, 1.0);
    tex0 = texCoord;

    normal0 = normalize(model * vec4(vertexNormal, 0.0)).xyz;
   	world0 = (model * vec4(position, 1.0)).xyz;

    vis0 = calcFog(fog, mvPos);
}
