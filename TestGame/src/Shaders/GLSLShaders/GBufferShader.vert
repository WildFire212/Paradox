#version 330 
layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 texCoords; 
layout (location = 2) in vec3 normals; 
layout (location = 3) in vec3 tangents; 
layout (location = 4) in vec3 bitTangents; 

out DATA
{
vec3 FragPos;
vec2 TexCoords;
//vec3 Normal;
mat3 TBN; 
}vs_out; 

uniform mat4 T_model;
uniform mat4 T_view;
uniform mat4 T_projection;

void main()
{
    vec4 worldPos = T_model * vec4(pos, 1.0);
    vs_out.FragPos = worldPos.xyz; 
    vs_out.TexCoords = texCoords;
    
	
    //mat3 normalMatrix = transpose(inverse(mat3(T_model)));
    //vs_out.Normal = normalMatrix * normals;
	
	vec3 T = normalize(vec3 (T_model * vec4(tangents, 0.0)));
	vec3 N = normalize(vec3(T_model * vec4(normals , 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N , T);
        vs_out.TBN = mat3(T,B,N);
	
    gl_Position = T_projection * T_view * worldPos;
}