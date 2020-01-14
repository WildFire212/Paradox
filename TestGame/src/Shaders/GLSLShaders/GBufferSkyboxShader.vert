#version 330

layout (location = 0) in vec3 pos;

out DATA
{
out vec3 TexCoords;
out vec4 FragPos; 
}vs_out; 

uniform mat4 T_projection;
uniform mat4 T_view;

void main()
{
	vs_out.TexCoords = pos;
	gl_Position = T_projection * T_view *vec4(pos, 1.0);
	vs_out.FragPos= T_projection * T_view *vec4(pos, 1.0);
}