#version 330 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in DATA{
 vec3 FragPos;
 vec2 TexCoords;
 vec3 Normal;
 }fs_in; 

 struct Material{ 
	float specularIntensity; 
	float shininess; 
	sampler2D diffuseTexture;
 };


uniform Material M_material; 

void main()
{    
   
    gPosition.xyz = fs_in.FragPos.xyz;
    gPosition.w = M_material.shininess; 

    gNormal = normalize(fs_in.Normal);
    gAlbedoSpec.rgb = texture(M_material.diffuseTexture, fs_in.TexCoords).rgb; 
    gAlbedoSpec.a = M_material.specularIntensity; 
}