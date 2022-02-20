#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fColor;

uniform mat4 uNormalMatrix;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uDirectionalLightsDirections_vs[32];
uniform vec3 uDirectionalLightsIntensities[32];
uniform int uDirectionalLightCount;

uniform vec3 uPointLightsPositions_vs[32];
uniform vec3 uPointLightsIntensities[32];
uniform float uPointLightsAttenuations[32];
uniform int uPointLightCount;

uniform sampler2D uTexture;
uniform bool uHasTexture;

uniform sampler2D uNormalMap;
uniform bool uHasNormalMap;

const vec3 ambient = vec3(0.00);

vec3 getNormal()
{
	return uHasNormalMap ?
            (uNormalMatrix * vec4(2.0 * texture(uNormalMap, vTexCoords).xyz - 1.0, 0)).xyz
			:
			vNormal_vs;
}

vec3 blinnPhongDirectionalLight(int index) {
	vec3 lightDirection = uDirectionalLightsDirections_vs[index];
	vec3 lightIntensity = uDirectionalLightsIntensities[index];

	vec3 wi = normalize(lightDirection);
	vec3 w0 = normalize(- vPosition_vs);

	vec3 normal = normalize(getNormal());

	vec3 halfway = normalize(lightDirection + w0);

	vec3 diffuse = uKd * max(0.0, dot(wi, normal));

	vec3 specular = uKs * pow(max(0.0, dot(halfway, normal)), uShininess);

	return lightIntensity * (diffuse + specular + ambient);
}

vec3 blinnPhongPointLight(int index) {
	vec3 lightPosition = uPointLightsPositions_vs[index];
	vec3 lightIntensity = uPointLightsIntensities[index];
	float lightAttenuationFactor = uPointLightsAttenuations[index];

	vec3 wi = normalize(lightPosition - vPosition_vs);
	vec3 w0 = normalize(- vPosition_vs);

	vec3 normal = normalize(getNormal());

	vec3 halfway = normalize(wi + w0);

	vec3 diffuse = uKd * max(0.0, dot(wi, normal));
	vec3 specular = uKs * pow(max(0.0, dot(halfway, normal)), uShininess);

	float lightDistance = distance(lightPosition, vPosition_vs);
	float attenuation = 1 + lightAttenuationFactor * lightDistance * lightDistance;

	return lightIntensity * (diffuse + specular + ambient) / attenuation;
}

vec3 getColor()
{
	return uHasTexture ? texture(uTexture, vTexCoords).rgb : vec3(1);
}

void main() {
	
	vec3 lights = vec3(0);
	vec3 light = vec3(0);

	for(int i = 0; i < uDirectionalLightCount; i++)
	{
		// light = blinnPhongDirectionalLight(i);
		// lights += light;
		lights += blinnPhongDirectionalLight(i);
	}

	for(int j = 0; j < uPointLightCount; j++)
	{
		// light = blinnPhongPointLight(j);
		// lights += light; // ???????????????????????????????
		lights += blinnPhongPointLight(j);
	}

	fColor = getColor() * lights;
};