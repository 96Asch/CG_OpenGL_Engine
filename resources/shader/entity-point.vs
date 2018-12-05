#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec2 texCoord;
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

uniform struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float hasTexture;
    float reflectance;
    float hasFakeLighting;
} material;

uniform mat4 mv;
uniform mat4 mvp;


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

  toLightVector = pointLight.position - mvPos.xyz;

	mvVertexPos = -mvPos.xyz;

  mvVertexNormal = surfaceNormal;
}
