#version 430 core
#extension GL_NV_shadow_samplers_cube : enable

const float lowerLimit = -10.0f;
const float upperLimit = 30.0;


in vec3 texCoords;

out vec4 fragColor;

uniform samplerCube map1;
uniform vec3 fogColor;

void main(void){

	vec4 texture1 = textureCube(map1, texCoords);

	float factor = (texCoords.y - lowerLimit) / (upperLimit - lowerLimit);
	factor = clamp(factor, 0.0, 1.0);
	fragColor = mix(vec4(fogColor, 1.0), texture1, factor);
}
