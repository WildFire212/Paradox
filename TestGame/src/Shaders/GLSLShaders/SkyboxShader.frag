#version 330

in DATA{
in vec3 TexCoords;
}fs_in; 

out vec4 colour;

uniform samplerCube skybox;

void main()
{
	colour = texture(skybox, fs_in.TexCoords);
}