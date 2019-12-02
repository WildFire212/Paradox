#version 330 
layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 texCoords; 
layout (location = 2) in vec3 normals; 

out DATA
{
out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
}vs_out; 

uniform mat4 T_model;
uniform mat4 T_view;
uniform mat4 T_projection;

void main()
{
    vec4 worldPos = T_model * vec4(pos, 1.0);
    vs_out.FragPos = worldPos.xyz; 
    vs_out.TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(T_model)));
    vs_out.Normal = normalMatrix * normals;

    gl_Position = T_projection * T_view * worldPos;
}