#version 330 core

layout (location = 0) in  vec3 vVertex;
layout (location = 1) in  vec3 vNormal;
//in  vec4 vColor;

smooth out vec3 normal;
smooth out vec3 lightDir;
smooth out vec4 eyePos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec4 light_Pos;

void main() {
	mat3 normalMatrix = mat3(transpose(inverse(model)));
	normal = normalMatrix * vNormal; 
	eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(light_Pos.xyz - eyePos.xyz); /// Create the light direction
	gl_Position =  projMatrix * modelViewMatrix * vVertex; 
	
}