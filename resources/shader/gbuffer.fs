#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in TD_DATA {
  vec2 tex0;
  vec3 normal0;
  vec3 world0;
} inData;


uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = inData.world0;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(inData.normal0);
    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(texDiffuse, inData.tex0).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(texSpecular, inData.tex0).r;
}
