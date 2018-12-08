#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 tex0;

void main()
{
    tex0 = uv;
    gl_Position = vec4(position, 1.0);
}
