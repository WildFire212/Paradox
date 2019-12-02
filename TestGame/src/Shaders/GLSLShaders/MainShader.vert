#version 330 
layout ( location = 0) in vec3 pos; 
layout (location = 2 ) in vec3 normals; 
uniform mat4 model ;
uniform mat4 view; 
uniform mat4 projection; 

out DATA{
vec4 color; 
vec3 Normal; 
vec3 FragPos; 
}vs_out;
void main(){
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vs_out.color = vec4(clamp(pos,0.0,1.0),1.0); 
	vs_out.Normal = normals; 
	vs_out.FragPos = (model * vec4(pos, 1.0)).xyz; 
}