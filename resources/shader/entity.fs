#version 430 core

const int MAX_POINT_LIGHTS = 5;

const float specularPower = 10;
const vec3 ambientLight = vec3(0.3);

in vec2 outTexCoord;
in vec3 mvVertexNormal;
in vec3 mvVertexPos;
in vec3 toLightVector[MAX_POINT_LIGHTS];
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
    float hasFakeLighting;
    float hasNormalMap;
} material;

uniform struct Fog {
	float isActive;
	vec3 color;
	float density;
	float gradient;
} fog;

uniform sampler2D texture_sampler;
// uniform sampler2D normalMap;

vec4 ambientC;
vec4 diffuseC;
vec4 speculrC;

void setupColours(Material material, vec2 textCoord) {
    if (material.hasTexture == 1) {
        ambientC = texture2D(texture_sampler, textCoord);
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


vec4 calcDirectionalLight(DirectionalLight light, vec3 position, vec3 normal) {
    return calcLightColour(light.color, light.intensity, position, normalize(light.direction), normal);
}

vec4 setFog(vec4 currColour, Fog f, float vis) {
	vec4 outColour = vec4(0);
	if (f.isActive == 1) {
		outColour = mix(vec4(f.color, 1.0), currColour, vis);
	}
	else {
		outColour = currColour;
	}

	return outColour;
}


// vec3 calcNormal(vec3 currNormal, sampler2D normalMap, vec2 outTexCoord, Material mat) {
// 	vec3 normal = currNormal;
//
// 	if(mat.hasNormalMap == 1) {
// 		vec4 normalMapValue = 2.0 * texture2D(normalMap, outTexCoord) - 1.0;
// 		normal = normalize(normalMapValue.rgb);
// 	}
//
// 	return normal;
// }

void main() {
    setupColours(material, outTexCoord);

    // vec3 normal = calcNormal(mvVertexNormal, normalMap, outTexCoord, material);
    vec3 normal = mvVertexNormal;
    if(material.hasTexture == 1 && ambientC.a < 0.5) {
    	discard;
    }

    if(material.hasNormalMap == 1){

    }

    vec4 diffuseSpecularComp = calcDirectionalLight(directionalLight, mvVertexPos, normal);

	for(int i = 0; i < MAX_POINT_LIGHTS; i++){
        if ( pointLight[i].intensity > 0 )
        {
            diffuseSpecularComp += calcPointLight(pointLight[i], mvVertexPos, normal, toLightVector[i]);
        }
    }

    fragColor = ambientC * vec4(ambientLight, 1) + diffuseSpecularComp;
    fragColor = setFog(fragColor, fog, visibility);
}
