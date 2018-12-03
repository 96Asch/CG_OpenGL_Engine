#version 430 core

const int MAX_POINT_LIGHTS = 5;
const int MAX_TEXTURES = 5;
const float specularPower = 10;
const float tiling = 80;
const vec4 blueTint = vec4(0,0,0.5,0);

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;
in vec3 worldPos;
in float visibility;

out vec4 fragColor;


struct BaseLight {
  vec3 color;
  float intensity;
};

uniform struct PointLight {
    BaseLight light;
    vec3 position;
    vec3 attenuation;
} pointLight[MAX_POINT_LIGHTS];


uniform struct DirectionalLight {
    BaseLight light;
    vec3 direction;
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
uniform vec3 ambientLight;
uniform sampler2D textures[MAX_TEXTURES];
uniform vec3 camPosition;

vec4 ambientC = vec4(0);
vec4 diffuseC = vec4(0);
vec4 speculrC = vec4(0);
float reflectance = 0;

vec4 calcTextureColors(vec2 texCoords) {
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

  return result;
}

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal) {
  vec4 diffuseColor = vec4(0);
  vec4 specularColor = vec4(0);

  float dFactor = max(dot(normal, -direction), 0.0);
  diffuseColor = vec4(light.color, 1.0) * light.intensity * dFactor;

  vec3 camDirection = normalize(camPosition - worldPos);
  vec3 reflectDirection = normalize(reflect(direction, normal));

  float specularFactor = max(dot(camDirection, reflectDirection), 0.0);
  specularFactor = pow(specularFactor, specularPower);

  specularColor = vec4(light.color, 1.0) * reflectance * specularFactor;

  return diffuseColor + specularColor;
}

// vec4 calcPointLight(PointLight light, vec3 position, vec3 normal, vec3 toLightVector) {
//   vec3 lightDir = toLightVector;
//   float distance = length(lightDir);
//   vec3 toLightDir  = normalize(lightDir);
//   vec4 lightColor = calcLightColor(light.color, light.intensity, position, toLightDir, normal);
//
//   float attenuationInv = light.attenuation.x + light.attenuation.y * distance +
//                          light.attenuation.z * distance * distance;
//   return lightColor / attenuationInv;
// }

vec4 calcPLight(PointLight pLight, vec3 normal) {
  vec3 lightDirection = worldPos - pLight.position;
  float distance = length(lightDirection);
  lightDirection = normalize(lightDirection);

  vec4 color = calcLight(pLight.light, lightDirection, normal);

  float attenuation = pLight.attenuation.x +
                      pLight.attenuation.y * distance +
                      pLight.attenuation.z * distance * distance +
                      0.0001;

  return color / attenuation;
}


vec4 calcDLight(DirectionalLight dLight, vec3 normal) {
  return calcLight(dLight.light, -dLight.direction, normal);
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
  vec4 texColor = calcTextureColors(outTexCoord);
  vec3 normal = normalize(mvVertexNormal);
  vec4 light = vec4(ambientLight, 1.0);

  light += calcDLight(directionalLight, normal);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
    if ( pointLight[i].light.intensity > 0 ) {
        light += calcPLight(pointLight[i], normal);
    }
  }

  fragColor = texColor * light;
  // fragColor = setFog(fragColor, fog, visibility);
}
