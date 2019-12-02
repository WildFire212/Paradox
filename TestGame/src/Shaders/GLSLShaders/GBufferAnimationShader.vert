#version 330 
layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 texCoords; 
layout (location = 2) in vec3 normals; 
layout (location = 3) in vec2 boneData1; 
layout (location = 4) in vec2 boneData2; 
layout (location = 5) in vec2 boneData3; 
layout (location = 6) in vec2 boneData4; 

out DATA
{
out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
}vs_out; 

uniform mat4 T_model;
uniform mat4 T_view;
uniform mat4 T_projection;

uniform mat4 gBones[200]; 
void main()
{
	mat4 BoneTransform = gBones[uint(boneData1.x)] * boneData1.y;//+
			BoneTransform +=			gBones[uint(boneData2.x)] * boneData2.y ;//+
			BoneTransform +=			gBones[uint(boneData3.x)] * boneData3.y ;//+
			BoneTransform +=			gBones[uint(boneData4.x)] * boneData4.y;
	
	vec4 position = BoneTransform *   vec4(pos, 1.0);//BoneTransform * 
    vec4 worldPos = T_model * position;
    vs_out.FragPos = worldPos.xyz; 
    vs_out.TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(T_model)));
    vs_out.Normal = normalMatrix * normals;

    gl_Position = T_projection * T_view * worldPos;
}