#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in TD_DATA {
  vec3 world0;
  vec2 tex0;
  vec3 normal0;
} inData;


const int MAX_TEXTURES = 5;
const int tiling = 80;
float reflectance = 0;

uniform int numMaterials;
uniform sampler2D texDiffuse[MAX_TEXTURES];
uniform float specular[MAX_TEXTURES-1];

vec4 calcTextureColors(vec2 texCoords) {
  vec4 diffuse[MAX_TEXTURES - 1] = vec4[MAX_TEXTURES - 1](vec4(0),
                                                         vec4(0),
                                                         vec4(0),
                                                         vec4(0));
  vec2 tiled = texCoords * tiling;
  for(int i = 0; i < numMaterials; i++) {
      diffuse[i] = texture2D(texDiffuse[i+1], tiled);
  }

  vec4 blendmapCol = texture2D(texDiffuse[0], texCoords);
  float blackFactor = 1 - (blendmapCol.r + blendmapCol.g + blendmapCol.b);
  vec4 result = blackFactor * diffuse[0]
              + blendmapCol.r * diffuse[1]
              + blendmapCol.g * diffuse[2]
              + blendmapCol.b * diffuse[3];

  reflectance = blackFactor * specular[0]
              + blendmapCol.r * specular[1]
              + blendmapCol.g * specular[2]
              + blendmapCol.b * specular[3];
  return result;
}

void main() {
    vec4 fragColor = calcTextureColors(inData.tex0);
    gPosition = inData.world0;
    gNormal = normalize(inData.normal0);
    gAlbedoSpec.rgb = fragColor.rgb;
    gAlbedoSpec.a = reflectance;

}
