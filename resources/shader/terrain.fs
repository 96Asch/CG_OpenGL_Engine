#version 430 core

const int MAX_POINT_LIGHTS = 5;
const int MAX_TEXTURES = 5;
const float specularPower = 10;
const vec3 ambientLight = vec3(0.1,0.1,0.1);
const float tiling = 80;
const vec4 blueTint = vec4(0,0,0.5,0);

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;
in vec3 toLightVector[MAX_POINT_LIGHTS];
in vec3 worldPos;
in float visibility;

out vec4 fragColor;

uniform struct PointLight {
    vec3 color;
    vec3 position;
    float intensity;
    vec3 attenuation;
} pointLight[MAX_POINT_LIGHTS];


uniform struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float intensity;
} directionalLight;

uniform struct Material {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float hasTexture;
  float reflectance;
} materials[MAX_TEXTURES];

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform int numMaterials;
uniform sampler2D textures[MAX_TEXTURES];

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
  vec3 toLightDir  = normalize(lightDir);
  vec4 lightColor = calcLightColor(light.color, light.intensity, position, toLightDir, normal);

  float distance = length(lightDir);
  float attenuationInv = light.attenuation.x + light.attenuation.y * distance +
                         light.attenuation.z * distance * distance;
  return lightColor / attenuationInv;
}


vec4 calcDirectionalLight(DirectionalLight light, vec3 position, vec3 normal) {
  return calcLightColor(light.color, light.intensity, position, normalize(light.direction), normal);
}

vec4 setFog(vec4 currColor, Fog f, float vis) {
	vec4 outColor = vec4(0);
	if (f.isActive == 1) {
		outColor = mix(vec4(f.color, 1.0), currColor, vis);
	}
	else {
		outColor = currColor;
	}
	return outColor;
}


void main() {
  setupCurrentColors(outTexCoord);

  vec4 diffuseSpecularComp = calcDirectionalLight(directionalLight, mvVertexPos, mvVertexNormal);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
    if ( pointLight[i].intensity > 0 ) {
        diffuseSpecularComp += calcPointLight(pointLight[i], mvVertexPos, mvVertexNormal, toLightVector[i]);
    }
  }

  fragColor = ambientC * vec4(ambientLight, 1) + diffuseSpecularComp;
  fragColor = setFog(fragColor, fog, visibility);
}
