#version 330

layout (location = 0) out vec4 gPosition; 
layout (location = 1) out vec3 gNormal
layout (location = 2) out vec4 gAlbedoSpec; 

in DATA{
in vec3 TexCoords;
in vec3 FragPos; 
}fs_in;


uniform samplerCube skybox;

void main()
{
	gPosition.xyz = fs_in.FragPos.xyz ; 
	gPosition.w = 1.0; 
	
	gNormal = vec3(0,0,0); 
	gAlbedoSpec.rgb= texture(skybox, fs_in.TexCoords);
	gAlbedoSpec.a = 1.0; 

}