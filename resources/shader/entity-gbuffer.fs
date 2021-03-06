#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in TD_DATA {
  vec3 world0;
  vec2 tex0;
  vec3 normal0;
} inData;

uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;

void main() {
    gPosition = inData.world0;
    gNormal = normalize(inData.normal0);
    gAlbedoSpec.rgb = texture(texDiffuse, inData.tex0).rgb;
    gAlbedoSpec.a = texture(texSpecular, inData.tex0).r;
}
