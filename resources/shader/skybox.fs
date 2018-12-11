#version 430 core
#extension GL_NV_shadow_samplers_cube : enable

in vec3 texCoords;

out vec4 fragColor;

uniform samplerCube map1;

void main(void){

	fragColor = textureCube(map1, texCoords);

}
