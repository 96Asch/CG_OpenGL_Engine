#version 430 core

const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;

in vec2 tex0;
in vec3 normal0;
in vec3 world0;
in float vis0;

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

uniform struct Material {
  vec4 diffuse;
  float specularPower;
  float hasTexture;
  float reflectance;
} material;

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform vec3 ambientLight;
uniform sampler2D texture;
uniform sampler2D shadowMap;
uniform vec3 camPosition;

float specularPower = 0;
float reflectance = 0;

vec4 calcTextureColors(vec2 texCoords) {
  vec4 color = vec4(0);
  if(material.hasTexture == 1) {
    color = texture2D(texture, texCoords);
  }
  else {
    color = material.diffuse;
  }
  specularPower = material.specularPower;
  reflectance = material.reflectance;
  return color;
}

vec4 calcLight(BaseLight light, vec3 direction, vec3 normal) {
  vec4 diffuseColor = vec4(0);
  vec4 specularColor = vec4(0);

  float dFactor = max(dot(normal, -direction), 0.0);
  diffuseColor = vec4(light.color, 1.0) * light.intensity * dFactor;

  vec3 camDirection = normalize(camPosition - world0);
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
  vec3 lightDirection = world0 - pLight.position;
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
    vec3 lightDirection = normalize(world0 - light.point.position);
    float spotFactor = dot(lightDirection, light.direction);
    vec4 color = vec4(0);
    if(spotFactor > light.cutoff) {
        float fadeFactor = 1.0 - ((1.0 - spotFactor) / (1.0 - light.cutoff));
        color = calcPLight(light.point, normal) * fadeFactor;
    }
    return color;
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
  vec4 texColor = calcTextureColors(tex0);
  vec3 normal = normalize(normal0);
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
  fragColor = setFog(fragColor, fog, vis0);
}
