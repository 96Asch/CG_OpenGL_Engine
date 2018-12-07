#version 430 core

const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;
const float specularPower = 10;


in TD_DATA {
  vec2 tex0;
  vec3 normal0;
  vec3 world0;
} inData;

out vec4 fragColor;


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
uniform sampler2D texture;
uniform sampler2D specular;
uniform vec3 camPosition;

float reflectance = 0;

vec4 calcTextureColors(vec2 texCoords) {
  vec4 color = texture2D(texture, texCoords);
  reflectance = texture2D(specular, texCoords).r;
  return color;
}

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal) {
  vec4 diffuseColor = vec4(0);
  vec4 specularColor = vec4(0);

  float dFactor = max(dot(normal, -direction), 0.0);
  diffuseColor = vec4(light.color, 1.0) * light.intensity * dFactor;

  vec3 camDirection = normalize(camPosition - inData.world0);
  vec3 reflectDirection = normalize(reflect(direction, normal));

  float specularFactor = max(dot(camDirection, reflectDirection), 0.0);
  specularFactor = pow(specularFactor, specularPower);

  specularColor = vec4(light.color, 1.0) * reflectance * specularFactor;

  return diffuseColor + specularColor;
}

vec4 calcDLight(DirectionalLight dLight, vec3 normal) {
  return calcLight(dLight.light, -dLight.direction, normal);
}

vec4 calcPLight(PointLight pLight, vec3 normal) {
  vec3 lightDirection = inData.world0 - pLight.position;
  float distance = length(lightDirection);

  if(distance > pLight.range) {
      return vec4(0.0);
  }

  lightDirection = normalize(lightDirection);

  vec4 color = calcLight(pLight.light, lightDirection, normal);

  float attenuation = pLight.attenuation.x +
                      pLight.attenuation.y * distance +
                      pLight.attenuation.z * distance * distance +
                      0.0001;

  return color / attenuation;
}

vec4 calcSLight(SpotLight light, vec3 normal) {
    vec3 lightDirection = normalize(inData.world0 - light.point.position);
    float spotFactor = dot(lightDirection, light.direction);
    vec4 color = vec4(0);
    if(spotFactor > light.cutoff) {
        float fadeFactor = 1.0 - ((1.0 - spotFactor) / (1.0 - light.cutoff));
        color = calcPLight(light.point, normal) * fadeFactor;
    }
    return color;
}


void main() {
  vec4 texColor = calcTextureColors(inData.tex0);
  vec3 normal = normalize(inData.normal0);
  vec4 light = vec4(ambientLight, 1.0);

  light += calcDLight(directionalLight, normal);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
    if ( pointLight[i].light.intensity > 0 ) {
        light += calcPLight(pointLight[i], normal);
    }
  }

  for(int i = 0; i < MAX_SPOT_LIGHTS; i++) {
    if ( spotLight[i].point.light.intensity > 0 ) {
        light += calcSLight(spotLight[i], normal);
    }
  }

  fragColor = texColor * light;
  // fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
