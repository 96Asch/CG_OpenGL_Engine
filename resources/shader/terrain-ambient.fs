#version 430 core

const float tiling = 80;
const int MAX_TEXTURES = 5;

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;

out vec4 fragColor;

uniform struct Material {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float hasTexture;
  float reflectance;
} materials[MAX_TEXTURES];

uniform int numMaterials;
uniform sampler2D textures[MAX_TEXTURES];
uniform vec3 ambient;

vec4 ambientC = vec4(0);
vec4 diffuseC = vec4(0);
vec4 speculrC = vec4(0);
float reflectance = 0;

void setupCurrentColors(vec2 texCoords) {
  vec4 ambient[MAX_TEXTURES - 1] = vec4[MAX_TEXTURES - 1](vec4(0),
                                                         vec4(0),
                                                         vec4(0),
                                                         vec4(0));
  vec2 tiled = texCoords * tiling;
  for(int i = 0; i < numMaterials; i++) {
    if(materials[i].hasTexture == 1) {
      ambient[i] = texture2D(textures[i+1], tiled);
    }
    else {
      ambient[i] = materials[i].ambient;
    }
  }

  vec4 blendmapCol = texture2D(textures[0], texCoords);
  float blackFactor = 1 - (blendmapCol.r + blendmapCol.g + blendmapCol.b);
  vec4 result = blackFactor * ambient[0]
              + blendmapCol.r * ambient[1]
              + blendmapCol.g * ambient[2]
              + blendmapCol.b * ambient[3];

  reflectance = blackFactor * materials[0].reflectance
              + blendmapCol.r * materials[1].reflectance
              + blendmapCol.g * materials[2].reflectance
              + blendmapCol.b * materials[3].reflectance;

  ambientC = result;
  diffuseC = result;
  speculrC = result;
}


void main() {
  setupCurrentColors(outTexCoord);
  fragColor = ambientC * vec4(ambient, 1) ;
}
