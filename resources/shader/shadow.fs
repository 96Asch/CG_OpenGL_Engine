#version 430 core

in vec2 tex0;

out vec4 fragColor;

uniform sampler2D shadowMap;

void main() {
    float depth = texture2D(shadowMap, tex0).x;
    depth = 1.0 - (1.0 - depth) * 25.0;
    fragColor = vec4(depth);
}
