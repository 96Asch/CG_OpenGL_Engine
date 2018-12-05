#version 430 core

const float specularPower = 10;

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;
in vec3 toLightVector;

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
    float hasFakeLighting;
} material;

uniform sampler2D texture;
vec4 ambientC;
vec4 diffuseC;
vec4 speculrC;

void setupColours(Material material, vec2 textCoord) {
    if (material.hasTexture == 1) {
        ambientC = texture2D(texture, textCoord);
        diffuseC = ambientC;
        speculrC = ambientC;
    }
    else {
        ambientC = material.ambient;
        diffuseC = material.diffuse;
        speculrC = material.specular;
    }
}

vec4 calcLightColour(vec3 light_colour, float light_intensity, vec3 position, vec3 to_light_dir, vec3 normal) {
    vec4 diffuseColour = vec4(0, 0, 0, 0);
    vec4 specColour = vec4(0, 0, 0, 0);

    // Diffuse Light
    float diffuseFactor = max(dot(normal, to_light_dir), 0.0);
    diffuseColour = diffuseC * vec4(light_colour, 1.0) * light_intensity * diffuseFactor;

    // Specular Light
    vec3 camera_direction = normalize(position);
    vec3 from_light_dir = -to_light_dir;
    vec3 reflected_light = normalize(reflect(from_light_dir , normal));
    float specularFactor = max( dot(camera_direction, reflected_light), 0.0);
    specularFactor = pow(specularFactor, specularPower);
    specColour = speculrC * light_intensity  * specularFactor * material.reflectance * vec4(light_colour, 1.0);

    return (diffuseColour + specColour);
}

vec4 calcPointLight(PointLight light, vec3 position, vec3 normal, vec3 toLightVector) {
    vec3 light_direction = toLightVector;
    vec3 to_light_dir  = normalize(light_direction);
    vec4 light_colour = calcLightColour(light.color, light.intensity, position, to_light_dir, normal);

    // Apply Attenuation
    float distance = length(light_direction);
    float attenuationInv = light.attenuation.x + light.attenuation.y * distance +
        light.attenuation.z * distance * distance;
    return light_colour / attenuationInv;
}


void main() {
  setupColours(material, outTexCoord);

  vec4 pLight = calcPointLight(pointLight, mvVertexPos, mvVertexNormal, toLightVector);


  fragColor = ambientC * pLight;
}
