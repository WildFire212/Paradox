#version 330 
#include"LightingData.glsl"

in DATA{
vec2 TexCoords;
}fs_in; 

vec3 FragPos; 
vec3 Normal; 

uniform sampler2D gPosition ; 
uniform sampler2D gNormal; 
uniform sampler2D gAlbedoSpec;

uniform vec3 eyePosition;

uniform SpotLight spotLight; 

out vec4 color; 


Material material;






void main(){
	//color = vec4 (1,0 ,1,1);
	FragPos  =  texture(gPosition, fs_in.TexCoords).rgb;
	material.shininess = texture(gPosition,fs_in.TexCoords).a; 
	Normal =  texture(gNormal, fs_in.TexCoords).rgb;
	material.specularIntensity = texture(gAlbedoSpec, fs_in.TexCoords).a;
	

	vec4 totalColor = CalcSpotLight(spotLight,material,Normal, FragPos, eyePosition); 
	color = vec4(texture(gAlbedoSpec, fs_in.TexCoords).rgb ,1.0) * totalColor; 
	//color = vec4(0.0,0.0,1.0,1.0);
}




