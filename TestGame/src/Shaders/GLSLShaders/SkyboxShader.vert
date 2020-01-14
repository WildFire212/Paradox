#version 330

layout (location = 0) in vec3 pos;

out DATA{
out vec3 TexCoords;
}vs_out;
uniform mat4 T_projection;
uniform mat4 T_view;

void main()
{
	vs_out.TexCoords = pos;
	vec4 posw = T_projection * T_view * vec4(pos, 1.0);
	gl_Position =posw.xyww
}