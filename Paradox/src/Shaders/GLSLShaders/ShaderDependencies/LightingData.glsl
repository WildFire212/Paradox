

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight{
	Light base; 
	vec3 direction; 
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};


struct Material{
	float specularIntensity; 
	float shininess; 
};



vec4 CalcLightByDirection(Light light, vec3 direction,Material material ,vec3 Normal,vec3 FragPos, vec3 eyePosition)
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColour);
}


vec4 CalcDirectionalLight(DirectionalLight directionalLight,Material material ,vec3 Normal,vec3 FragPos, vec3 eyePosition)
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction,material,Normal ,FragPos, eyePosition);
}

vec4 CalcPointLight(PointLight pLight,Material material,vec3 Normal,vec3 FragPos, vec3 eyePosition )
 {
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	
	vec4 colour = CalcLightByDirection(pLight.base, direction,material,Normal, FragPos, eyePosition);
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
	
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight,Material material, vec3 Normal,vec3 FragPos, vec3 eyePosition)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	if(slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base,material,Normal,FragPos, eyePosition);
		
		return colour * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}
}
