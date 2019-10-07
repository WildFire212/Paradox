#version 330 
#include"LightingData.glsl"
in DATA{
vec4 color; 
vec3 Normal; 
vec3 FragPos; 
}fs_in; 

out vec4 color; 

uniform vec3 eyePosition;

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform Material material;




vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	
		totalColour += CalcPointLight(pointLight);
	
	
	return totalColour;
}

vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
			
	totalColour += CalcSpotLight(spotLight);
	
	return totalColour;
}	



void main(){
	//color = vec4 (1,0 ,1,1);
	vec4 totalColor = CalcDirectionalLight(directionalLight); 

	color = fs_in.color * totalColor; 
}




