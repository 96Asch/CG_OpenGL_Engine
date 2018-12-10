#version 430 core

const int MAX_POINT_LIGHTS = 30;
const int MAX_SPOT_LIGHTS = 30;
const float specularPower = 10;

in vec2 tex0;

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;


struct BaseLight {
  vec3 color;
  float intensity;
};

uniform struct DirectionalLight {
  BaseLight light;
  vec3 direction;
} directionalLight;

uniform struct PointLight {
  BaseLight light;
  vec3 position;
  vec3 attenuation;
  float range;
} pointLight[MAX_POINT_LIGHTS];

uniform struct SpotLight {
  PointLight point;
  vec3 direction;
  float cutoff;
} spotLight[MAX_SPOT_LIGHTS];

uniform vec3 ambientLight;
uniform vec3 camPosition;
uniform sampler2D gAlbedoSpec;
uniform sampler2D gPosition;
uniform sampler2D gNormal;

float reflectance = 0;

vec4 calcTextureColors(vec2 texCoords) {
  vec4 diffuse = vec4(texture2D(gAlbedoSpec, texCoords).rgb, 1.0);
  reflectance = texture2D(gAlbedoSpec, texCoords).a;
  return diffuse;
}

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal, vec3 fragPosition) {
  vec4 diffuseColor = vec4(0);
  vec4 specularColor = vec4(0);

  float dFactor = max(dot(normal, -direction), 0.0);
  diffuseColor = vec4(light.color, 1.0) * light.intensity * dFactor;

  vec3 camDirection = normalize(camPosition - fragPosition);
  vec3 reflectDirection = normalize(reflect(direction, normal));

  float specularFactor = max(dot(camDirection, reflectDirection), 0.0);
  specularFactor = pow(specularFactor, specularPower);

  specularColor = vec4(light.color, 1.0) * reflectance * specularFactor;

  return diffuseColor + specularColor;
}

vec4 calcDLight(DirectionalLight dLight, vec3 normal, vec3 fragPosition) {
  return calcLight(dLight.light, -dLight.direction, normal, fragPosition);
}

vec4 calcPLight(PointLight pLight, vec3 normal, vec3 fragPosition) {
  vec3 lightDirection = fragPosition - pLight.position;
  float distance = length(lightDirection);

  if(distance > pLight.range) {
      return vec4(0.0);
  }

  lightDirection = normalize(lightDirection);

  vec4 color = calcLight(pLight.light, lightDirection, normal, fragPosition);

  float attenuation = pLight.attenuation.x +
                      pLight.attenuation.y * distance +
                      pLight.attenuation.z * distance * distance +
                      0.0001;

  return color / attenuation;
}

vec4 calcSLight(SpotLight light, vec3 normal, vec3 fragPosition) {
    vec3 lightDirection = normalize(fragPosition - light.point.position);
    float spotFactor = dot(lightDirection, light.direction);
    vec4 color = vec4(0);
    if(spotFactor > light.cutoff) {
        float fadeFactor = 1.0 - ((1.0 - spotFactor) / (1.0 - light.cutoff));
        color = calcPLight(light.point, normal, fragPosition) * fadeFactor;
    }
    return color;
}


void main() {

  vec4 texColor = calcTextureColors(tex0);
  vec3 fragPos = texture(gPosition, tex0).rgb;
  vec3 normal = texture(gNormal, tex0).rgb;
  vec4 light = vec4(ambientLight, 1.0);

  light += calcDLight(directionalLight, normal, fragPos);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
    if ( pointLight[i].light.intensity > 0 ) {
        light += calcPLight(pointLight[i], normal, fragPos);
    }
  }

  for(int i = 0; i < MAX_SPOT_LIGHTS; i++) {
    if ( spotLight[i].point.light.intensity > 0 ) {
        light += calcSLight(spotLight[i], normal, fragPos);
    }
  }

  fragColor = texColor * light;
  float brightFactor = (fragColor.r * 0.2126) +
                          (fragColor.g * 0.7152) +
                              (fragColor.b * 0.0722);
  brightColor = fragColor * brightFactor * 0.5;
}
