#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
out DATA{
vec2 TexCoords;
}vs_out;

void main()
{
    vs_out.TexCoords = texCoords; 
    gl_Position = vec4(pos,1.0);
}