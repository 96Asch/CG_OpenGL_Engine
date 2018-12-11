#version 430 core

layout (location=0) in vec3 position;

out vec3 texCoords;

uniform mat4 pv;

void main(void){

	gl_Position = pv * vec4(position, 1.0);
	texCoords = position;

}
