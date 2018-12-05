#version 430 core

const int MAX_TEXTURES = 5;
const float specularPower = 10;
const float tiling = 80;

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;
in vec3 toLightVector;

out vec4 fragColor;

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
} materials[MAX_TEXTURES];

uniform int numMaterials;
uniform sampler2D textures[MAX_TEXTURES];
uniform sampler2D shadowMap;

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
      ambient[i] = texture2D(shadowMap, tiled);
      //textures[i+1]
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

vec4 calcLightColor(vec3 lightColor, float lightIntensity, vec3 position, vec3 toLightDir, vec3 normal) {
  vec4 diffuseColor = vec4(0, 0, 0, 0);
  vec4 specColor = vec4(0, 0, 0, 0);

  float diffuseFactor = max(dot(normal, toLightDir), 0.0);
  diffuseColor = diffuseC * vec4(lightColor, 1.0) * lightIntensity * diffuseFactor;

  vec3 cameraDir = normalize(position);
  vec3 fromLightDir = -toLightDir;
  vec3 reflectLight = normalize(reflect(fromLightDir , normal));
  float specularFactor = max( dot(cameraDir, reflectLight), 0.0);
  specularFactor = pow(specularFactor, specularPower);
  specColor = speculrC * lightIntensity  * specularFactor * reflectance * vec4(lightColor, 1.0);

  return (diffuseColor + specColor);
}

vec4 calcPointLight(PointLight light, vec3 position, vec3 normal, vec3 toLightVector) {
  vec3 lightDir = toLightVector;
  float distance = length(lightDir);
  lightDir = normalize(lightDir);
  vec4 lightColor = calcLightColor(light.color, light.intensity, position, lightDir, normal);
  float attenuationInv = light.attenuation.x + light.attenuation.y * distance +
                         light.attenuation.z * distance * distance + 0.000001f;
  return lightColor / attenuationInv;
}



void main() {
  setupCurrentColors(outTexCoord);

  vec4 pLight = calcPointLight(pointLight, mvVertexPos, mvVertexNormal, toLightVector);

  fragColor = ambientC * pLight;
}
