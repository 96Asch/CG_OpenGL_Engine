#version 430 core

const int MAX_POINT_LIGHTS = 5;

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 vertexNormal;

out vec2 outTexCoord;
out vec3 mvVertexNormal;
out vec3 mvVertexPos;
out vec3 toLightVector[MAX_POINT_LIGHTS];
out float visibility;

uniform struct PointLight {
    vec3 color;
    vec3 position;
    float intensity;
    vec3 attenuation;
} pointLight[MAX_POINT_LIGHTS];

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float hasTexture;
    float reflectance;
    float hasFakeLighting;
} material;

// uniform struct TextureOffset {
// 	float numberOfRows;
// 	vec2 offset;
// } tex;

uniform mat4 model;
uniform mat4 mv;
uniform mat4 mvp;

float calcFog(Fog f, vec4 positionRelativeToCam) {

  float vis = 0;
  if(f.isActive == 1.0) {
  	float distance = length(positionRelativeToCam.xyz);
  	vis = exp(-pow((distance* f.density), f.gradient));
  	vis = clamp(vis,0.0,1.0);
  }
	return vis;
}

void main()
{
	vec4 worldPosition = model * vec4(position,1.0);

  vec4 mvPos = mv * vec4(position,1.0);
  gl_Position = mvp * vec4(position,1.0);

  // outTexCoord = (texCoord / tex.numberOfRows) + tex.offset;
  outTexCoord = texCoord;
  vec3 normal = vertexNormal;

  if(material.hasFakeLighting == 1){
  	normal = vec3(0,1,0);
  }

  vec3 surfaceNormal = normalize(mv * vec4(normal, 0.0)).xyz;

	for(int i = 0; i < MAX_POINT_LIGHTS; i++){
		toLightVector[i] = pointLight[i].position - mvPos.xyz;
	}

	mvVertexPos = -mvPos.xyz;

  mvVertexNormal = surfaceNormal;
  visibility = calcFog(fog, mvPos);
}
