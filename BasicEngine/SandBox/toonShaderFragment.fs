#version 330 core

in  vec3 normal;
in  vec3 lightDir;
in  vec4 eyePos;
out vec4 fragColor;


void main() { 

	float intensity = dot(lightDir,normal);
	
	//Dot can never be negative
	float silhouette = max(dot(normal,normalize(-eyePos.xyz)), 0.0);
	
	if (silhouette < 0.2){
		fragColor = vec4(0.0, 0.0, 0.0, 1.0);	
	}else if (intensity > 0.95){
		fragColor = vec4(1.0, 0.5, 0.5, 1.0);
	}else if (intensity > 0.5){
		fragColor = vec4(0.6, 0.3, 0.3, 1.0);
	}else if (intensity > 0.25){
		fragColor = vec4(0.4, 0.2, 0.2, 1.0);
	}else{
		fragColor = vec4(0.2, 0.1, 0.1, 1.0);
	}
} 