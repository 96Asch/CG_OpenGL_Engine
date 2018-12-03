#version 430 core

const int MAX_POINT_LIGHTS = 5;

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 vertexNormal;

out vec2 outTexCoord;
out vec3 mvVertexNormal;
out vec3 mvVertexPos;
out vec3 worldPos;
out float visibility;

struct BaseLight {
  vec3 color;
  float intensity;
};

uniform struct PointLight {
    BaseLight light;
    vec3 position;
    vec3 attenuation;
} pointLight[MAX_POINT_LIGHTS];

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform mat4 model;
uniform mat4 mvp;
uniform mat4 mv;
// uniform vec4 clipPlane;

float calcFog(Fog f, vec4 positionRelativeToCam) {
	float vis = 0;
	float distance = length(positionRelativeToCam.xyz);
	vis = exp(-pow((distance* f.density), f.gradient));
	vis = clamp(vis,0.0,1.0);
	return vis;
}

void main() {
	// // gl_ClipDistance[0] = dot(worldPosition, clipPlane);
  // gl_ClipDistance[0] = dot(worldPosition, vec4(0.0));
    gl_Position = mvp * vec4(position, 1.0);
    vec4 mvPos = model * vec4(position, 1.0);
    outTexCoord = texCoord;

  //
  //  	mvVertexPos = -mvPos.xyz;
    mvVertexNormal = normalize(model * vec4(vertexNormal, 0.0)).xyz;
   	worldPos = (model * vec4(position, 1.0)).xyz;

    visibility = calcFog(fog, mvPos);
}
