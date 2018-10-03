#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
	TexCoords = aPos;
	//View->clip(does not need to be bothered with world position)
	vec4 pos = projection * view * vec4(aPos,1.0);
	gl_Position = pos.xyww;//Set z to w so z(depth) is always 1, reuslts in NDC
}
	
